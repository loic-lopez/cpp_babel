// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Server.hpp created 28/09/2017

#pragma once

#include <NonCopyable.hpp>
#include "IServer.hpp"
#include "User.hpp"
#include "ConvInfo.hpp"
#include "IPlugin.hpp"
#include <Logger.hpp>
#include <TCPBoost.hpp>
#include <sstream>
#include <fstream>
#include <boost/thread/thread.hpp>

namespace Server
{
    constexpr static int SAVE_TIME = 5;

    class ServerCore : public IServer, public Alfred::NonCopyable
    {
      public:
        ServerCore();
        virtual ~ServerCore();

        using Username = std::string;
        using ID = std::string;

        /**
         * @brief Map of username linked with the id on the server
         */
        std::map<Username, ID> _indexUserServer;
        std::map<ID, Username> _indexIdUser;
        std::map<std::string, struct UserInfo> _users;
        ConvInfo *_convInfo;
        std::map<std::string, Plugin::IPlugin *> _plugins;
        Network::IServerCommunicator *_comm;
        Database::IDatabase *_db;
        std::string _pathPlugin;
        bool _stop = false;
        unsigned _refreshSaveTimer = SAVE_TIME;

        Network::IServerCommunicator &getNetwork() override;
        Database::IDatabase &getDatabase(std::string name) override;
        IServer &clientConnected(std::string client_id) override;
        IServer &clientDisconnected(const std::string &client_id) override;
        IServer &analyzeRequest(std::string client_id, Protocol::ProtocolData cmd) override;
        IServer &loadConfig(const std::string &string) override;
        IServer &loadDB(const std::string &name) override;
        IServer &loadNetwork(int port) override;
        IServer &loadPluginFolder(const std::string &path) override;
        IServer &loopPlugin() override;
        IServer &sendPluginInstalled() override;
        IServer &refreshPlugin(const std::string &path) override;
        IServer &run() override;
        IServer &stop() override;
        IServer &save() override;

        struct Protocol::ProtocolData makeError(enum Protocol::ErrorCodes);
        int getTime();

        IServer &account_login(const std::string &client_id, Protocol::ProtocolData cmd);
        IServer &account_create(const std::string &client_id, Protocol::ProtocolData cmd);

        IServer &sendResponse(std::string client_id, Protocol::ProtocolData msg) override;
        void add_contact(std::string basic_string, Protocol::ProtocolData data);
        void send_friend_list(std::string basic_string);
        void send_friend_request(std::string client_id, const std::string &);
        void user_accept_contact(std::string data, Protocol::ProtocolData protocolData);
        void user_deny_contact(std::string data, Protocol::ProtocolData protocolData);
        bool verifyUserLogged(const std::string &client_id);
        void userCallUser(const std::string &client_id, Protocol::ProtocolData protocolData);
        void userAcceptCall(const std::string &client_id, Protocol::ProtocolData protocolData);
        void userDenyCall(const std::string &client_id, Protocol::ProtocolData protocolData);

        Protocol::ProtocolData makePacket(Protocol::ServerToClient cmd);
    };
}
