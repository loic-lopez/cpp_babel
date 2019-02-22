// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// SenderUDP.hpp created 05/10/2017

#pragma once

#include <QUdpSocket>
#include "ISoundStream.hpp"
#include "ISenderNetwork.hpp"
#include "Logger.hpp"


namespace Network
{
    class SenderUDP : public QThread, public ISenderNetwork
    {
      Q_OBJECT

      private:
        QUdpSocket *udpSocket;
        std::string ip;
        quint16     port;
        Sound::ISoundStream *soundStream;

      public:
        SenderUDP(const std::string &ip, quint16 port = 6642, Sound::ISoundStream *soundStream = nullptr);
        ~SenderUDP() override;

        ISenderNetwork &Connect() override;
        ISenderNetwork &Send(Protocol::SoundPacket packet, Sound::EncodedSound) override;
        ISenderNetwork &Stop() override;
        void run() override;
        ISenderNetwork  &Start() override;

      signals:
        void error(QUdpSocket::SocketError socketError);
    };
}
