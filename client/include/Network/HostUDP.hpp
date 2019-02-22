// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// HostUDP.hpp created 05/10/2017

#pragma once

#include <QWidget>
#include <QUdpSocket>
#include <QThread>
#include "IHostNetwork.hpp"

namespace Network
{
    class   HostUDP : public QThread, public IHostNetwork
    {
      Q_OBJECT

      private:
        QUdpSocket  *udpSocket;
        quint16     port;
        bool _stop;

        std::function<void(Protocol::SoundPacket, Sound::EncodedSound)> _function;

      public:
        HostUDP(quint16 port = 6666);
        ~HostUDP() override;

        IHostNetwork &Host() override;
        IHostNetwork &onReceive(std::function<void(Protocol::SoundPacket, Sound::EncodedSound)> function) override;
        IHostNetwork &Stop() override;
        void run() override;
        IHostNetwork &Start() override;
    };
}

