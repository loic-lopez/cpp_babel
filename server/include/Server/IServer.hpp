// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// IServer.hpp created 28/09/2017

#pragma once

#include "IServerCommunicator.hpp"
#include "IDatabase.hpp"
#include "IPlugin.hpp"
#include "codes.hpp"

namespace Server
{
    /**
     * @brief Interface for the Server
     */
    class IServer
    {
      public:
        IServer()
        {
        }

        virtual ~IServer()
        {
        }

        /**
         * @brief Return the Network Communicator
         * @return Network Communicator
         */
        virtual Network::IServerCommunicator &getNetwork()= 0;

        virtual Database::IDatabase &getDatabase(std::string name)= 0;
        virtual IServer &analyzeRequest(std::string client_id, Protocol::ProtocolData cmd) =0;
        virtual IServer &clientConnected(const std::string client_id) = 0;
        virtual IServer &clientDisconnected(const std::string &client_id) = 0;
        virtual IServer &loadConfig(const std::string &) =0;
        virtual IServer &loadDB(const std::string &name) =0;
        virtual IServer &loadNetwork(int port) =0;
        virtual IServer &loadPluginFolder(const std::string &path)= 0;
        virtual IServer &loopPlugin() =0;
        virtual IServer &sendPluginInstalled() = 0;
        virtual IServer &refreshPlugin(const std::string &path) =0;
        virtual IServer &run() =0;
        virtual IServer &stop() = 0;
        virtual IServer &save() =0;
        virtual IServer &sendResponse(std::string client_id, Protocol::ProtocolData msg) =0;
    };
}