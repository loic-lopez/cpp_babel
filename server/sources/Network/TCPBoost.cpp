// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// INetworkBoost.cpp created 28/09/2017

#include <Logger.hpp>
#include <boost/thread/thread.hpp>
#include "TCPBoost.hpp"

namespace Network
{
    TCPBoost::~TCPBoost()
    {
    }

    TCPBoost::TCPBoost() :
        _endpoint(boost::asio::ip::tcp::v4(), DEFAULT_PORT),
        _acceptor(_io_service, _endpoint)
    {
        LOG.log("Starting server on port " + std::to_string(DEFAULT_PORT));
        start_accept();
    }

    TCPBoost::TCPBoost(unsigned port) :
        _endpoint(boost::asio::ip::tcp::v4(), port),
        _acceptor(_io_service, _endpoint)
    {
        LOG.log("Starting server on port " + std::to_string(port));
        start_accept();
    }

    TCPBoost::TCPBoost(const std::string &, unsigned port) :
        _endpoint(boost::asio::ip::tcp::v4(), port),
        _acceptor(_io_service, _endpoint)
    {
        LOG.error("Passing ip at server creation is useless because it will always be  localhost");
        LOG.log("Starting server on port " + std::to_string(port));
        start_accept();
    }

    ConnectionInfo &TCPBoost::getClientInfo(std::string client_id)
    {
        auto conn = new ConnectionInfo;
        conn->ip = _clientsConnected[client_id].get()->socket().remote_endpoint().address().to_string();
        return *conn;
    }

    std::unordered_map<int, ConnectionInfo> &TCPBoost::getClients()
    {
        return _client_infos;
    }

    IServerCommunicator &TCPBoost::onConnect(const std::function<void(IServerCommunicator *, std::string)> &_func)
    {
        _onConnectFunc = _func;
        return *this;
    }

    IServerCommunicator &TCPBoost::onDisconnect(const std::function<void(IServerCommunicator *, std::string)> &_func)
    {
        _onDisconnectFunc = _func;
        return *this;
    }

    int TCPBoost::operator[](unsigned)
    {
        return 0;
    }

    IServerCommunicator &TCPBoost::run()
    {
        boost::asio::signal_set signals(_io_service, SIGINT);
        signals.async_wait([&] (const boost::system::error_code& , int) {
            LOG.warning("[NETWORK] Stopping...");
            this->stop();
        });
        _io_service.run(); //maybe needed another thread
        return *this;
    }

    IServerCommunicator &TCPBoost::Send(std::string client_id, Protocol::ProtocolData data)
    {
        if (_clientsConnected.count(client_id) == 0)
            LOG.error("[NETWORK] Error while trying to send a message to " + client_id + " dont exist");
        else
            _clientsConnected[client_id]->Send(data);
        return *this;
    }

    IServerCommunicator &TCPBoost::stop()
    {
        _io_service.stop();
        LOG.log("Server stopped");
        return *this;
    }

    IServerCommunicator &TCPBoost::setConnectionMode(ConnectionMode)
    {
        return *this;
    }

    void TCPBoost::start_accept()
    {
        session_ptr new_session(new TCPBoostSession(_io_service));
        _acceptor.async_accept(new_session->socket(),
                               boost::bind(&TCPBoost::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void TCPBoost::handle_accept(session_ptr session, const boost::system::error_code &error)
    {
        if (!error) {
            session->onDisconnect([&] (std::string s) -> void {
                this->_onDisconnectFunc(this, s);
            });
            LOG.warning("[NETWORK] New connection: " + session->getId());
            _clientsConnected[session->getId()] = session;
            _onConnectFunc(this, session->getId());
            session->onReceive([this](std::string client_id, Protocol::ProtocolData data) -> void {
                this->_onReceiveFunc(this, client_id, data);
            });
            boost::thread workerThread([&] () { session->start(); });
//            session->start();
        }
        start_accept();
    }

    IServerCommunicator &
    TCPBoost::onReceive(
        const std::function<void(IServerCommunicator *, std::string client_id, Protocol::ProtocolData)> &_func)
    {
        _onReceiveFunc = _func;
        return *this;
    }
}