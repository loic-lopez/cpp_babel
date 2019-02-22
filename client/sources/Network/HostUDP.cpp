// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// HostUDP.cpp created 05/10/2017

#include "HostUDP.hpp"

Network::HostUDP::HostUDP(quint16 port)
{
    this->udpSocket = new QUdpSocket(this);
    QHostAddress    address;
    address.setAddress("0.0.0.0");

    this->udpSocket->bind(address, port);
    this->port = port;
    _stop = false;
}

Network::HostUDP::~HostUDP()
{
    delete this->udpSocket;
}

Network::IHostNetwork &
Network::HostUDP::onReceive(std::function<void(Protocol::SoundPacket, Sound::EncodedSound)> function)
{
    _function = function;
    return *this;
}

Network::IHostNetwork &Network::HostUDP::Stop()
{
    this->udpSocket->close();
    return *this;
}

Network::IHostNetwork &Network::HostUDP::Host()
{
    while (!_stop)
    {
        Protocol::SoundPacket *soundPacket = new Protocol::SoundPacket;

        this->udpSocket->waitForReadyRead();
        this->udpSocket->readDatagram(reinterpret_cast<char *>(soundPacket), Protocol::SOUND_PACKET_SIZE);

        if (soundPacket->magiccode != Protocol::MAGIC_CODE_SOUND_PACKET)
            continue;

        auto x = new char[soundPacket->size];

        this->udpSocket->waitForReadyRead();
        this->udpSocket->readDatagram(x, soundPacket->size);

        Sound::EncodedSound enc;
        enc.resize(soundPacket->size);
        for (int i = 0; i < soundPacket->size; i++)
            enc[i] = x[i];
        _function(*soundPacket, enc);
    }
    return *this;
}

Network::IHostNetwork &Network::HostUDP::Start()
{
    this->start();
}

void Network::HostUDP::run()
{
    this->Host();
}
