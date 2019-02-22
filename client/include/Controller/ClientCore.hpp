// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// ClientCore.hpp created 03/10/17

#pragma once

#include <QApplication>
#include <QObject>
#include <QtCore/QProcess>
#include "NonCopyable.hpp"
#include "HostUDP.hpp"
#include "SenderUDP.hpp"
#include "IClient.hpp"
#include "Logger.hpp"
#include "Graphics.hpp"
#include "qtNetwork.hpp"
#include "User.hpp"
#include "Chat.hpp"

namespace Controller
{
    constexpr static int DEFAULT_PORT_HOST_UDP = 6666;

    class ClientCore : public QObject, public IClient, public Alfred::NonCopyable
    {
        Q_OBJECT

      public slots:
        void getServerData(Protocol::ProtocolData data);
        void getServerDC();
      signals:
        void getData(Protocol::ProtocolData data);
        void notifyServerDC();
        void NETSendQT(Protocol::ProtocolData data);

      private:
        View::IGraphics *_graphics;
        Network::INetworkClient *_network;
        Sound::ISoundStream *_streamer;
        Sound::ISoundCodec *_codec;

        Network::IHostNetwork *_udpHost;
        Network::ISenderNetwork *_udpSend;

        std::map<int, Chat> _convs;
        UserInfo _user;
        QApplication _app;
        QThread _NET;
        QThread _UDPSEND;
        QThread _UDPRECEIVE;

        QProcess *_HOST;
        QProcess *_SENDER;

//        int _lastTimeStampTCP = 0;

        std::function<void (void)> _onReceiveOk;
        std::function<void (void)> _onReceiveBadLoginFormat;
        std::function<void (void)> _onReceiveIncorrectLogin;
        std::function<void (void)> _onReceiveUserAlreadyExist;
        std::function<void (void)> _onReceiveUserDontExist;
        std::function<void (void)> _onReceiveUserOffline;
        std::function<void (void)> _onReceiveUserAlreadyInGroup;
        std::function<void (void)> _onReceiveUserAlreadyYourFriend;
        std::function<void (void)> _onReceiveGroupDontExist;
        std::function<void (void)> _onReceiveMessageDontExist;
        std::function<void (void)> _onReceiveCantMessageYourself;
        std::function<void (void)> _onReceiveCantModifyAnotherUserMessage;
        std::function<void (void)> _onReceiveCantCallYourself;
        std::function<void (void)> _onReceiveUserAlreadyInCall;
        std::function<void (void)> _onReceiveUnknowError;

        std::string _bro;
        std::string _caller;
        std::string _ip_other;
        int _port_other;

        std::function<void(Protocol::ProtocolData)> _onReceiveFriendList;

        IClient &registerWindow();
        IClient *loginWindow();
        IClient &homeWindow();
        IClient &connectServerWindow();
        IClient &callWindow(const std::string &contact_name);
        IClient &callByFriendWindow(const std::string &contact_name);

      public:
        ClientCore();
        ~ClientCore() override;
        IClient &getGraphicEvent() override;
        View::ActionData getServerEvent() override;
        IClient &initGraphic() override;
        IClient &initNetwork(const std::string &ip, int port) override;
        IClient &initSound(int channels, int bufSize, int sampleRate) override;
        Sound::ISoundStream &getStreamer() override;
        Sound::ISoundCodec &getCodec() override;
        View::IGraphics &getGraphics() override;
        Network::INetworkClient &getNetwork() override;
        IClient &loadPlugin() override;
        IClient &loopPlugin() override;
        IClient &refreshPlugin() override;
        IClient &processGraphicEvent() override;
        IClient &processServerEvent(Protocol::ProtocolData) override;
        IClient &run() override;
        IClient &stop() override;
        IClient &errorWindow(const std::string &error);
        IClient &hostAndListenUDP(int port) override;
        IClient &connectAndSendUDP(std::string ip, int port) override;
        Protocol::ProtocolData makePacket(Protocol::ClientToServer cmd);
        IClient &successWindow(const std::string &msg = "Success");

        IClient &loginProcess(const std::string &username, const std::string &password);

        IClient &sendLoginCMD(std::string &login, std::string &password);
        IClient &sendRegisterCMD(std::string &login, std::string &password);
        IClient &sendNeedFriendList();
        IClient &sendFriendRequest(const std::string &username);
        IClient &callFriend(const std::string &username);
        void acceptCallFrom(std::string from, int port);
        void denyCallFrom(std::string from);

        IClient &receiveFriendList(Protocol::ProtocolData data);
        void receiveFriendRequest(Protocol::ProtocolData data);
        void receiveCallRequest(Protocol::ProtocolData data);
        void receiveCallAccept(Protocol::ProtocolData data);

        void HostFirst(std::string ip, int port);
        void HostSecond(std::string ip, int port);
    };
}