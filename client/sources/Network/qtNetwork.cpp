// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// qtNetwork.cpp created 29/09/2017

#include "qtNetwork.hpp"

Network::qtNetwork::qtNetwork()
{
    this->soc = new QTcpSocket(0);
}

Network::qtNetwork::qtNetwork(const unsigned port)
{
    this->port = port;
    this->soc = new QTcpSocket(0);
    soc->moveToThread(this);
}

Network::qtNetwork::qtNetwork(const std::string &ip, unsigned port)
{
    this->IP = QString::fromStdString(ip);
    this->port = port;
    this->soc = new QTcpSocket(0);
    soc->moveToThread(this);
}

Network::qtNetwork::~qtNetwork()
{
}

Network::INetworkClient &Network::qtNetwork::Connect()
{
    this->soc->connectToHost(this->IP, this->port);
    if (this->soc->waitForConnected())
        std::cout << "Connected!" << std::endl;
    else
        serverDc();
    return *this;
}

Network::INetworkClient &Network::qtNetwork::Connect(const std::string &ip, unsigned port)
{
    this->soc->connectToHost(QString::fromStdString(ip), port);
    if (this->soc->waitForConnected())
        std::cout << "Connected!" << std::endl;
    else
        serverDc();
    return *this;
}

Network::INetworkClient &Network::qtNetwork::Send(Protocol::ProtocolData data)
{
    if (this->soc->state() == QAbstractSocket::ConnectedState) {
        this->soc->write(reinterpret_cast<char *>(&data.header), sizeof(struct Protocol::PacketHeader));
        this->soc->write(data.data.c_str(), data.header.data_size);
        this->soc->waitForBytesWritten(3000000);
    }
    return *this;
}

Network::INetworkClient &Network::qtNetwork::Listen()
{
    Protocol::PacketHeader header;
    Protocol::ProtocolData data;

    this->soc->waitForReadyRead(3000000);
    auto len = soc->read(reinterpret_cast<char *>(&header), Protocol::HEADER_SIZE);

    if (len != Protocol::HEADER_SIZE) {
        LOG.error("server dc while getting header");
        serverDc();
        return *this;
    }

    if (header.magiccode != Protocol::MAGIC_CODE_PACKET_HEADER) {
        LOG.error("Wrong magic code");
        serverDc();
        return *this;
    }

    data.header = header;
    if (data.header.data_size == 0)
    {
        sendDataToMain(data);
        Listen();
    }

    auto arr = new char[header.data_size];

    this->soc->waitForReadyRead(300);
    len = soc->read(arr, header.data_size);
    if (len != data.header.data_size)
    {
        LOG.error("[NETWORK] Expected to receive " + std::to_string(data.header.data_size) + " received: " + std::to_string(len));
        LOG.error("server dc while getting body");
        serverDc();
        return *this;
    }
    data.data = arr;
    sendDataToMain(data);
    Listen();
    return *this;
}

Network::INetworkClient &Network::qtNetwork::sendThenListen(Protocol::ProtocolData data)
{
    this->Send(data);
    this->Listen();
    return *this;
}

Network::INetworkClient &
Network::qtNetwork::onReceived(const std::function<void(Protocol::ProtocolData)> &func)
{
    _onReceived = func;
    return *this;
}

Network::INetworkClient &Network::qtNetwork::onDisconnect(std::function<void()> func)
{

    _on_disconnect = func;
    return *this;
}

void Network::qtNetwork::run()
{
    this->soc = new QTcpSocket(0);
    soc->setParent(0);
    soc->moveToThread(this);
    Connect();
    Listen();
}

Network::INetworkClient &Network::qtNetwork::Start_Async()
{
    start();
}

Network::INetworkClient &Network::qtNetwork::Stop_Async()
{
    soc->disconnectFromHost();
    this->metaObject()->invokeMethod(this, "terminate", Qt::QueuedConnection);
    terminate();
}

void Network::qtNetwork::QT_SEND(Protocol::ProtocolData data)
{
    this->Send(data);
}
