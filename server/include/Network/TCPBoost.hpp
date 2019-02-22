// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// i_network_boost.hpp created 28/09/2017

#pragma once

#define _WIN32_WINNT 0x0501

#include "IServerCommunicator.hpp"
#include "TCPBoostSession.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Random.hpp"

using session_ptr = boost::shared_ptr<TCPBoostSession>;

namespace Network
{
    class TCPBoost : public IServerCommunicator
    {
      private:
        boost::asio::io_service _io_service;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::acceptor _acceptor;

        std::map<std::string, session_ptr> _clientsConnected;

        std::unordered_map<int, Network::ConnectionInfo> _client_infos;

        std::function<void(IServerCommunicator *, std::string client_id, Protocol::ProtocolData data)> _onReceiveFunc = [] (IServerCommunicator *, std::string, Protocol::ProtocolData) -> void { LOG.fatal("You need to  define a function for receive"); };
        std::function<void(IServerCommunicator *, std::string client_id)> _onConnectFunc = [] (IServerCommunicator *, std::string) -> void { LOG.fatal("You need to declare a function for onConnect"); };
        std::function<void(IServerCommunicator *, std::string client_id)> _onDisconnectFunc = [] (IServerCommunicator *, std::string) -> void { LOG.fatal("You need to declare a function for onDisconnect"); };;

      public:
        TCPBoost();
        ~TCPBoost();
        explicit TCPBoost(unsigned port);
        TCPBoost(const std::string &ip, unsigned port);
        ConnectionInfo &getClientInfo(std::string client_id) override;
        std::unordered_map<int, ConnectionInfo> &getClients() override;
        IServerCommunicator &onConnect(const std::function<void(IServerCommunicator *, std::string)> &_func) override;
        IServerCommunicator &onDisconnect(const std::function<void(IServerCommunicator *, std::string)> &_func) override;
        IServerCommunicator &onReceive(const std::function<void(IServerCommunicator *, std::string client_id, Protocol::ProtocolData data)> &_func) override;
        int operator[](unsigned id) override;
        IServerCommunicator &run() override;
        IServerCommunicator &Send(std::string client_id, Protocol::ProtocolData data) override;
        IServerCommunicator &stop() override;
        IServerCommunicator &setConnectionMode(ConnectionMode mode) override;

        void start_accept();
        void handle_accept(session_ptr session, const boost::system::error_code &error);
    };
}
