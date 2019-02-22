// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// IServerCommunicator.hpp created 28/09/2017

#pragma once

#include <string>
#include <functional>
#include <map>
#include <unordered_map>
#include <protocol_server.hpp>

namespace Network
{
    constexpr unsigned short DEFAULT_PORT = 4000;

    class BindFailed : public std::exception
    {

      public:
        BindFailed();
        virtual ~BindFailed();

        BindFailed(const std::string &ip, int port)
            :
            msg(std::string("Failed to bind to ip: ") + ip + " and port " + std::to_string(port))
        {
        }

        virtual const char *what() const throw()
        {
            return msg.c_str();
        }

      private:
        std::string msg;
    };

    enum ConnectionMode
    {
        TCP = 0,
        UDP
    };

    struct ConnectionInfo
    {
      public:
        int id;
        std::string ip;
        unsigned port;
    };

    class IServerCommunicator
    {

      public:
        virtual ~IServerCommunicator() = default;

        virtual ConnectionInfo &getClientInfo(std::string client_id) =0;
        virtual std::unordered_map<int, ConnectionInfo> &getClients() =0;
        virtual IServerCommunicator &onConnect(const std::function<void(IServerCommunicator *, std::string client_id)> &_func) =0;
        virtual IServerCommunicator &onDisconnect(const std::function<void(IServerCommunicator *, std::string client_id)> &_func) =0;
        virtual IServerCommunicator &onReceive(const std::function<void(IServerCommunicator *, std::string client_id, Protocol::ProtocolData data)> &_func) =0;
        virtual int operator[](unsigned id) =0;
        virtual IServerCommunicator &run() =0;
        virtual IServerCommunicator &Send(std::string client_id, Protocol::ProtocolData data) =0;
        virtual IServerCommunicator &stop() =0;
        virtual IServerCommunicator &setConnectionMode(enum ConnectionMode) = 0;
    };
}