// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// INetworkClient.hpp created 29/09/2017

#pragma once

#include <functional>
#include <exception>
#include <string>
#include "protocol_server.hpp"
#include <iostream>

namespace Network
{
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

            return NULL;
        }

      private:
        std::string msg;
    };

    struct ConnectionInfo
    {
        int id;
        unsigned port;
        std::string ip;
    };

    enum ConnectionMode
    {
        TCP = 0,
        UDP
    };

    class INetworkClient
    {
      public:
        virtual ~INetworkClient()
        {};
        virtual INetworkClient &Connect() = 0;
        virtual INetworkClient &Connect(const std::string &ip, unsigned port) = 0;
        virtual INetworkClient &Send(Protocol::ProtocolData data) = 0;
        virtual INetworkClient &Listen() = 0;
        virtual INetworkClient &sendThenListen(Protocol::ProtocolData data) = 0;
        virtual INetworkClient &onReceived(const std::function<void(Protocol::ProtocolData data)> &func) = 0;
        virtual INetworkClient &onDisconnect(std::function<void()> func) = 0;
        virtual INetworkClient &Start_Async() = 0;
        virtual INetworkClient &Stop_Async() = 0;
//Et la send qui est virtual oklm
    };
}