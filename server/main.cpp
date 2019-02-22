// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// main.cpp created 28/09/2017

#include <Logger.hpp>
#include <ServerCore.hpp>

#include "DatabaseTXT.hpp"

int main(int , char *[])
{
    //TODO REMIND: Server (TCPBOOST) store a map of client_id and session. And ServerCore store a map of username -> client_id. So it can translate an username to a client_id
    Server::IServer *s = new Server::ServerCore();

    s->loadConfig("./config");

    s->loadNetwork(4000);
    s->loadDB("./database");
    s->loadPluginFolder("./plugin");

    //TODO ON CONNECT

    s->getNetwork().onConnect([&] (Network::IServerCommunicator *, std::string client_id) {
        s->clientConnected(client_id);
    });

    s->getNetwork().onReceive([s] (Network::IServerCommunicator *, std::string client_id, Protocol::ProtocolData data) -> void {
        s->analyzeRequest(client_id, data);
    });

    s->getNetwork().onDisconnect([s] (Network::IServerCommunicator *, std::string id) -> void {
        LOG.log("A client was disconnected: " + id);
        s->clientDisconnected(id);
    });

    s->run();

    return 0;
}