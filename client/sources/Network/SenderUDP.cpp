// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// SenderUDP.cpp created 05/10/2017

#include "SenderUDP.hpp"

Network::SenderUDP::SenderUDP(const std::string &ip, quint16 port, Sound::ISoundStream *soundStream)
{
    this->udpSocket = new QUdpSocket(this);
    this->ip = ip;
    this->port = port;
    this->soundStream = soundStream;
}

Network::SenderUDP::~SenderUDP()
{
    delete this->udpSocket;
}

Network::ISenderNetwork &Network::SenderUDP::Connect()
{
    this->udpSocket->connectToHost(this->ip.c_str(), this->port);
    LOG.log("[UDP SEND] Trying to connect to host");
    udpSocket->waitForConnected(30000);
    if (udpSocket->state() == QUdpSocket::ConnectedState)
        LOG.warning("[UDP SEND] Connected to host");
    else
        LOG.fatal("[UDP SEND] Failed to connect to host");
    return *this;
}

Network::ISenderNetwork &Network::SenderUDP::Send(Protocol::SoundPacket packet, Sound::EncodedSound enc)
{
    auto sound = new char[packet.size];

    this->udpSocket->write(reinterpret_cast<char *>(&packet), Protocol::SOUND_PACKET_SIZE);
    this->udpSocket->waitForBytesWritten();

    for (int j = 0; j < packet.size; ++j)
        sound[j] = 0, sound[j] = enc[j];

    this->udpSocket->write(sound, packet.size);
    this->udpSocket->waitForBytesWritten();
    return *this;
}

Network::ISenderNetwork &Network::SenderUDP::Stop()
{
    this->udpSocket->close();
    return *this;
}

void Network::SenderUDP::run()
{
    soundStream->startStream();
}

Network::ISenderNetwork &Network::SenderUDP::Start()
{
    this->start();
}
