// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// TCPBoostSession.cpp created 29/09/2017

#include <iostream>
#include <Logger.hpp>
#include "TCPBoostSession.hpp"

void TCPBoostSession::start()
{
    do_read();
}

void TCPBoostSession::do_read()
{
    boost::asio::streambuf streamBuffer;
    boost::system::error_code error;

    boost::asio::read(_socket, streamBuffer.prepare(Protocol::HEADER_SIZE), error);

    if (error) {
        LOG.warning(std::string("[NETWORK] Client disconnected: ") + boost::system::system_error(error).what());
        _onDisconnect(_id);
        return;
    }

    streamBuffer.commit(Protocol::HEADER_SIZE);

    boost::asio::streambuf::const_buffers_type bufs = streamBuffer.data();
    std::string s(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + Protocol::HEADER_SIZE);

    auto header = (Protocol::PacketHeader *)s.c_str();

    LOG.log("[NETWORK] Received new packet from " + _id + " with command " + std::to_string(header->cmd));

    if (header->magiccode != Protocol::MAGIC_CODE_PACKET_HEADER) {
        LOG.error("[NETWORK] Bad magic code from " + _id);
        do_read();
        return;
    }

    _cmd.header = *header;
    if (header->data_size == 0)
    {
        _onReceiveFunc(_id, _cmd);
        do_read();
        return;
    }

    boost::asio::streambuf streamBufferData;
    boost::asio::read(_socket, streamBufferData.prepare(header->data_size), error);
    if (error) {
        LOG.warning(std::string("[NETWORK] Client disconnected: ") + boost::system::system_error(error).what());
        _onDisconnect(_id);
        return;
    }

    streamBufferData.commit(header->data_size);
    boost::asio::streambuf::const_buffers_type bufs_data = streamBufferData.data();
    std::string data(boost::asio::buffers_begin(bufs_data), boost::asio::buffers_begin(bufs_data) + header->data_size);
    _cmd.data = data;

    _onReceiveFunc(_id, _cmd);

    do_read();
}

void TCPBoostSession::do_write(const char *data, unsigned length)
{
    boost::asio::write(_socket, boost::asio::buffer(data, length));
}

boost::asio::ip::tcp::socket &TCPBoostSession::socket()
{
    return _socket;
}

TCPBoostSession::TCPBoostSession(boost::asio::io_service &socket) :
    _socket(socket)
{}

void TCPBoostSession::onReceive(std::function<void(std::string client_id, Protocol::ProtocolData data)> _func)
{
    _onReceiveFunc = _func;
}

void TCPBoostSession::Send(Protocol::ProtocolData data)
{
    do_write(reinterpret_cast<char *>(&data.header), sizeof(struct Protocol::PacketHeader));
    if (data.header.data_size != 0)
        do_write(data.data.c_str(), data.header.data_size);
}

const std::string &TCPBoostSession::getId() const
{
    return _id;
}

void TCPBoostSession::onDisconnect(std::function<void(std::string client_id)> _func)
{
    _onDisconnect = _func;
}