// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Server.cpp created 28/09/2017

#include <ServerCore.hpp>
#include <DatabaseTXT.hpp>
#include <Timer.hpp>

Server::ServerCore::ServerCore()
{
}

Server::ServerCore::~ServerCore()
{
}

Network::IServerCommunicator &Server::ServerCore::getNetwork()
{
    return *_comm;
}

Database::IDatabase &Server::ServerCore::getDatabase(std::string)
{
    return *_db;
}

Server::IServer &Server::ServerCore::loadConfig(const std::string &)
{
    LOG.error("Load config file is not implemented yet");
    return *this;
}

Server::IServer &Server::ServerCore::loadDB(const std::string &name)
{
    LOG.log("[DATABASE] Loading Dabatase " + name + "   (default = ./database)");
    _db = new Database::DatabaseTXT(name);

    _db->loadDatabase();

    LOG.log("[DATABASE] Database " + name + " loaded (default = ./database)");

    LOG.log("[DATABASE] Loading Table Member");

    _db->addTable("members");
    auto member = _db->getTable("members");


    LOG.log("[DATABASE] Parse member");
    member->parse([this](std::ifstream &file, Database::Rows &) -> void {
        std::stringstream s;
        s << file.rdbuf();
        boost::archive::xml_iarchive ia(s);
        std::vector<UserInfo> usersVec;
        ia >> BOOST_SERIALIZATION_NVP(usersVec);
        for (auto &it : usersVec)
        {
            LOG.log("[DATABASE] Member " + it.username + " found");
            _users[it.username] = it;
        }
    });

    member->setSaveFunction([this](std::ofstream &file, const Database::Rows &) -> void {
        boost::archive::xml_oarchive oa(file);
        std::vector<UserInfo> usersVec;
        for (auto &it: _users) {
            usersVec.push_back(it.second);
            LOG.log("[TABLE] [MEMBER] Saving member " + it.second.username);
        }
        oa << BOOST_SERIALIZATION_NVP(usersVec);
    });

    return *this;
}

Server::IServer &Server::ServerCore::loadNetwork(int port)
{
    _comm = new Network::TCPBoost(port);
    LOG.log("Network loaded on port " + std::to_string(port));
    return *this;
}

Server::IServer &Server::ServerCore::loopPlugin()
{
    std::vector<Plugin::PluginReturn> out;

    for (auto &it : _plugins) {
        auto tmp = it.second->execute();
        for (const auto &itv : tmp)
            out.push_back(itv);
    }

    return *this;
}

Server::IServer &Server::ServerCore::refreshPlugin(const std::string &)
{
    LOG.error("Need to implement refreshPlugin");

    return *this;
}

Server::IServer &Server::ServerCore::run()
{
    Alfred::Timer timer(_refreshSaveTimer);
    timer.start();

    boost::thread workerThread([this] () { _comm->run();  this->stop(); });

    while (!_stop) {
        if (timer.update()) {
//            LOG.log("[DATABASE] Saving in progress...");
//            _db->saveTables();
//            LOG.log("[DATABASE] Saving done");
            timer.restart();
        }
        loopPlugin();
    }
    LOG.log("[CORE] Stopping");
    _db->saveTables();
    _comm->stop();
    return *this;
}

Server::IServer &Server::ServerCore::save()
{
    LOG.log("Saving in progress, don't quit");

    return *this;
}

Server::IServer &Server::ServerCore::sendResponse(std::string client_id, Protocol::ProtocolData msg)
{
    LOG.log("Send response " + std::to_string(msg.header.cmd) + " to " + client_id);
    _comm->Send(client_id, msg);
    return *this;
}

Server::IServer &Server::ServerCore::sendPluginInstalled()
{

    return *this;
}

Server::IServer &Server::ServerCore::stop()
{
    _stop = true;
    return *this;
}

Server::IServer &Server::ServerCore::loadPluginFolder(const std::string &path)
{
    LOG.error("Plugin Loading not implemented yet");
    this->_pathPlugin = path;
    return *this;
}

struct Protocol::ProtocolData Server::ServerCore::makeError(enum Protocol::ErrorCodes reason)
{
    struct Protocol::ProtocolData err;

    err.header.cmd = Protocol::ServerToClient::ERROR;
    err.header.magiccode = Protocol::MAGIC_CODE_PACKET_HEADER;
    err.header.data_size = 0;
    err.header.timestamp = getTime();
    err.header.error = reason;
    return err;
}

int Server::ServerCore::getTime()
{
    return std::time(0);
}

Server::IServer &Server::ServerCore::clientDisconnected(const std::string &client_id)
{
    if (_indexIdUser.count(client_id) == 0) {
        LOG.log("This user was not logged and is now disconnected");
        return *this;
    }
    LOG.warning("User " + _indexIdUser[client_id] + " is now disconnected");
    _indexUserServer.erase(_indexIdUser[client_id]);
    _indexIdUser.erase(client_id);
    return *this;
}

Server::IServer &Server::ServerCore::clientConnected(const std::string client_id)
{
    (void) client_id;
    LOG.warning("[SERVER] A new (unknown) user is now connected !!! -> " + client_id);
    return *this;
}