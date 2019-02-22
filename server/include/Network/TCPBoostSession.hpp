// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// TCPBoostSession.hpp created 29/09/2017

#pragma once

#define _WIN32_WINNT 0x0501

#include <memory>
#include <boost/asio.hpp>
#include <commands.hpp>
#include <protocol_server.hpp>
#include <Random.hpp>

struct protocol_in
{
    struct Protocol::PacketHeader header;
    std::string data;
};

class TCPBoostSession : public std::enable_shared_from_this<TCPBoostSession>
{
  private:
    boost::asio::ip::tcp::socket _socket;
    struct Protocol::ProtocolData _cmd;
    std::string _id = Alfred::Random::string(20);

    std::function<void (std::string client_id, Protocol::ProtocolData data)> _onReceiveFunc;
    std::function<void (std::string client_id)> _onDisconnect;

  public:
    explicit TCPBoostSession(boost::asio::io_service &socket);

    const std::string &getId() const;
    void start();
    boost::asio::ip::tcp::socket &socket();
    void Send(Protocol::ProtocolData data);

    void onReceive(std::function<void (std::string client_id, Protocol::ProtocolData data)> _func);
    void onDisconnect(std::function<void (std::string client_id)>);

  private:
    void do_read();
    void do_write(const char *data, unsigned length);
};


