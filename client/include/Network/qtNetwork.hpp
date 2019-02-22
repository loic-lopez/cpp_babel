// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// qtNetwork.hpp created 29/09/2017

#pragma once

#include "INetworkClient.hpp"
#include "QThread"
#include <QObject>
#include <QTcpSocket>
#include <QHostInfo>
#include <QtWidgets/QDialog>
#include <QtNetwork/QNetworkSession>
#include "Logger.hpp"

namespace Network
{
    class qtNetwork : public QThread, public Network::INetworkClient
    {
      Q_OBJECT

      private:
        QString IP;
        int port;
        QTcpSocket *soc;
        QDataStream in;
        QNetworkSession *networkSession;

        std::function<void(Protocol::ProtocolData data)> _onReceived;
        std::function<void()> _on_disconnect;

      public:
        qtNetwork();
        explicit qtNetwork(const unsigned port);
        qtNetwork(const std::string &ip, unsigned port);
        ~qtNetwork() override;

        INetworkClient &Connect() override;
        INetworkClient &Connect(const std::string &ip, unsigned port) override;
        INetworkClient &Send(Protocol::ProtocolData data) override;
        INetworkClient &Listen() override;
        INetworkClient &sendThenListen(Protocol::ProtocolData data) override;
        INetworkClient &onReceived(const std::function<void(Protocol::ProtocolData)> &func) override;
        INetworkClient &onDisconnect(std::function<void()> func) override;
        INetworkClient &Start_Async() override;
        INetworkClient &Stop_Async() override;
        void run() override;

        signals:
          void sendDataToMain(Protocol::ProtocolData);
        void serverDc();

      public slots:
        void QT_SEND(Protocol::ProtocolData);
    };
}