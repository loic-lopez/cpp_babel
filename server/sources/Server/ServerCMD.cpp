// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// ServerCMD.cpp created 07/10/17

#include "ServerCore.hpp"

Server::IServer &Server::ServerCore::analyzeRequest(std::string client_id, Protocol::ProtocolData cmd)
{


    LOG.warning("[CORE] Receive new command: " + std::to_string(cmd.header.cmd));
    switch (cmd.header.cmd) {
        default:
            LOG.error("Case unknown " + std::to_string(cmd.header.cmd));
            sendResponse(client_id, makeError(Protocol::ErrorCodes::BAD_COMMAND));
            break;
        case Protocol::ClientToServer::ACCOUNT_LOGIN:
            account_login(client_id, cmd);
            break;
        case Protocol::ClientToServer::ACCOUNT_CREATE:
            account_create(client_id, cmd);
            break;
        case Protocol::ClientToServer::USER_ADD_CONTACT:
            add_contact(client_id, cmd);
            break;
        case Protocol::ClientToServer::USER_GET_ALL_FRIENDS:
            send_friend_list(client_id);
            break;
        case Protocol::ClientToServer::USER_ACCEPT_CONTACT:
            user_accept_contact(client_id, cmd);
            break;
        case Protocol::ClientToServer::USER_DENY_CONTACT:
            user_deny_contact(client_id, cmd);
            break;
        case Protocol::ClientToServer::CALL_DENY:
            userDenyCall(client_id, cmd);
            break ;
        case Protocol::ClientToServer::CALL_USER:
            userCallUser(client_id, cmd);
            break;
        case Protocol::ClientToServer::CALL_ACCEPT:
            userAcceptCall(client_id, cmd);
            break;
    }
    return *this;
}

struct Server::UserInfo &newUser(const std::string &username, const std::string &password)
{
    auto user = new Server::UserInfo;

    user->username = username;
    user->password = password;
    user->status = Protocol::Status::CONNECTED;
    user->pseudo = username;
    return *user;
}

Server::IServer &Server::ServerCore::account_login(const std::string &client_id, Protocol::ProtocolData cmd)
{
    LOG.log("[CMD] Login " + client_id);
    auto data = (struct Protocol::AccountLogin *)cmd.data.c_str();

    std::string username(data->username);
    std::string password(data->password);

    LOG.log("[CMD] [LOGIN] Username: " + username + " password: " + password);

    if (_indexUserServer.count(username) != 0) {
        //We only authorize one login / user (for now)
        LOG.warning(username + " try to login but already logged");
        sendResponse(client_id, makeError(Protocol::ErrorCodes::UNKNOWN_ERROR));
    }
    else if (_users.count(username) == 0 || _users[username].password != password) {
        if (_users.count(username) == 0)
        {
            LOG.warning(username + " try to login but dont exist");
            sendResponse(client_id, makeError(Protocol::ErrorCodes::USER_DONT_EXIST));
        }
        else
        {
            LOG.warning(username + " try to login with bad password (good / provided): " +
                        _users[username].password + " / " + password);
            sendResponse(client_id, makeError(Protocol::ErrorCodes::BAD_PASSWORD_OR_LOGIN));
        }
    } else {
        LOG.warning("[CMD] [LOGIN] Successfull login of user " + username);
        _indexUserServer[username] = client_id;
        _indexIdUser[client_id] = username;
        sendResponse(client_id, makeError(Protocol::ErrorCodes::OK));
        for (auto &it : _users[username].pendingInvites)
            send_friend_request(client_id, it);
    }
    return *this;
}

Server::IServer &Server::ServerCore::account_create(const std::string &client_id, Protocol::ProtocolData cmd)
{
    LOG.warning("[CMD] Register " + client_id);
    auto data = (struct Protocol::AccountCreate *)cmd.data.c_str();

    std::string username(data->username);
    std::string password(data->password);

    LOG.log("[CMD] [REGISTER] Username: " + username + " password: " + password);

    if (_users.count(username) != 0)
        {
            LOG.warning("[CMD] [REGISTER] Username already taken");
            sendResponse(client_id, makeError(Protocol::ErrorCodes::USER_ALREADY_EXIST));
            return *this;
        }
    LOG.warning("[SERVER] A new user is registered !!! -> " + username);
    _users[username] = newUser(username, password);
    _users[username].id = client_id;
    _indexUserServer[username] = client_id;
    _indexIdUser[client_id] = username;
    sendResponse(client_id, makeError(Protocol::ErrorCodes::OK));
    return *this;
}

void Server::ServerCore::add_contact(std::string client_id, Protocol::ProtocolData cmd)
{
    LOG.warning("[CMD] Add Contact " + client_id);

    auto data = (struct Protocol::UserAddContact *)cmd.data.c_str();

    std::string bro(data->username);

    LOG.log("[CMD] [ADD CONTACT] " + _indexIdUser[client_id] + " try to add " + bro);
    if (_indexIdUser[client_id] == bro)
    {
        LOG.warning("[CMD] [ADD CONTACT] cant add yourself");
        sendResponse(client_id, makeError(Protocol::ErrorCodes::UNKNOWN_ERROR));
        return;
    }
    if (_users.count(bro) == 0)
    {
        LOG.warning("[CMD] [ADD CONTACT] User don't exist " + bro);
        sendResponse(client_id, makeError(Protocol::ErrorCodes::USER_DONT_EXIST));
        return;
    }
    for (const auto &it : _users[_indexIdUser[client_id]].pendingInvites)
        if (it == bro)
        {
            sendResponse(client_id, makeError(Protocol::ErrorCodes::USER_ALREADY_YOUR_FRIEND));
            return;
        }

    for (const auto &x : _users[bro].pendingInvites)
        if (x == _indexIdUser[client_id])
        {
            LOG.warning("[CMD] [ADD CONTACT] Already in pending invites");
            sendResponse(client_id, makeError(Protocol::ErrorCodes::OK));
            return;
        }
    LOG.log("[CMD] [ADD CONTACT] Adding in waiting list");
    _users[bro].pendingInvites.push_back(_indexIdUser[client_id]);
    if (_indexUserServer.count(bro) != 0) //Online
         send_friend_request(_indexUserServer[bro], _indexIdUser[client_id]);
    sendResponse(client_id, makeError(Protocol::ErrorCodes::OK));
}

void Server::ServerCore::send_friend_list(std::string client_id)
{
    LOG.warning("[CMD] [SEND FRIEND LIST] to " + _indexIdUser[client_id]);
    Protocol::ProtocolData packet = makePacket(Protocol::ServerToClient::SEND_USER_LIST);
    struct Protocol::SendFriendList list;

    if (_users[_indexIdUser[client_id]].friendList.size() == 0)
    {
        LOG.warning("No friend");
        sendResponse(client_id, makeError(Protocol::ErrorCodes::UNKNOWN_ERROR));
        return;
    }

    std::memset(list.fri, 0, 32);
    size_t len = _users[_indexIdUser[client_id]].friendList[0].copy(list.fri, (sizeof list.fri) - 1);
    list.fri[len] = 0;

    packet.header.data_size = sizeof(struct Protocol::SendFriendList);
    packet.data = std::string(reinterpret_cast<char *>(&list), sizeof(struct Protocol::SendFriendList));
    sendResponse(client_id, packet);
}

Protocol::ProtocolData Server::ServerCore::makePacket(Protocol::ServerToClient cmd)
{
    Protocol::ProtocolData data;

    data.header.magiccode = Protocol::MAGIC_CODE_PACKET_HEADER;
    data.header.timestamp = std::time(0);
    data.header.cmd = cmd;
    return (data);
}

void Server::ServerCore::send_friend_request(std::string client_id, const std::string &bro)
{
    LOG.warning("Sending a new friend request from " + bro);
    auto packet = makePacket(Protocol::ServerToClient ::USER_HAS_SENT_FRIEND_REQUEST);

    Protocol::UserHasSentFriendRequest info;

    packet.header.data_size = sizeof(struct Protocol::UserHasSentFriendRequest);

    std::memset(info.username, 0, 32);
    size_t len = bro.copy(info.username, (sizeof info.username) - 1);
    info.username[len] = 0;
    packet.data = std::string(reinterpret_cast<char *>(&info), sizeof(struct Protocol::UserHasSentFriendRequest));
    sendResponse(client_id, packet);
}

void Server::ServerCore::user_accept_contact(std::string client_id, Protocol::ProtocolData protocolData)
{
    LOG.log("[CMD] [ACCEPT CONTACT] " + _indexIdUser[client_id]);
    Protocol::UserAcceptContact *d;

    d = (Protocol::UserAcceptContact *)protocolData.data.c_str();
    _users[d->username].friendList.push_back(_indexIdUser[client_id]);
    _users[_indexIdUser[client_id]].friendList.push_back(d->username);

    auto todel = std::find(_users[_indexIdUser[client_id]].pendingInvites.begin(), _users[_indexIdUser[client_id]].pendingInvites.end(), d->username);
    if (todel != _users[_indexIdUser[client_id]].pendingInvites.end())
        _users[_indexIdUser[client_id]].pendingInvites.erase(todel);

    sendResponse(client_id, makeError(Protocol::ErrorCodes::OK));

    LOG.log("[CMD] [HAS ACCEPTED FRIEND REQ] Online sending him the info " + std::string(d->username));


    if (_indexUserServer.count(d->username) == 0)
        return;

    Protocol::ProtocolData data = makePacket(Protocol::ServerToClient::USER_HAS_ACCEPTED_FRIEND);
    struct Protocol::UserInfo info;

    std::memset(info.username, 0, 32);
    size_t len = _users[_indexIdUser[client_id]].username.copy(info.username, (sizeof info.username) - 1);
    info.username[len] = 0;

    std::memset(info.city , 0, 32);
    len = _users[_indexIdUser[client_id]].city.copy(info.city, (sizeof info.city) - 1);
    info.city[len] = 0;

    std::memset(info.pseudo , 0, 32);
    len = _users[_indexIdUser[client_id]].pseudo.copy(info.pseudo, (sizeof info.pseudo) - 1);
    info.pseudo[len] = 0;

    std::memset(info.motd, 0, 512);
    len = _users[_indexIdUser[client_id]].motd.copy(info.motd, (sizeof info.motd) - 1);
    info.motd[len] = 0;

    struct Protocol::UserHasAcceptedFriendRequest acceptReq;
    data.header.data_size = sizeof(struct Protocol::UserHasAcceptedFriendRequest);
    acceptReq.info = info;

    data.data = std::string(reinterpret_cast<char *>(&acceptReq), sizeof(struct Protocol::UserHasAcceptedFriendRequest));
    sendResponse(_indexUserServer[d->username] , data);
}

void Server::ServerCore::user_deny_contact(std::string client_id, Protocol::ProtocolData protocolData)
{
    LOG.log("[CMD] [DENY CONTACT] " + _indexIdUser[client_id]);

    auto d = (Protocol::UserDenyContact *)protocolData.data.c_str();

    auto todel = std::find(_users[_indexIdUser[client_id]].pendingInvites.begin(), _users[_indexIdUser[client_id]].pendingInvites.end(), d->username);
    if (todel != _users[_indexIdUser[client_id]].pendingInvites.end())
        _users[_indexIdUser[client_id]].pendingInvites.erase(todel);

    sendResponse(client_id, makeError(Protocol::ErrorCodes::OK));
}

bool Server::ServerCore::verifyUserLogged(const std::string &client_id)
{
    if (_indexIdUser.count(client_id) == 0)
    {
        LOG.error("NON REGISTERED");
        sendResponse(client_id, makeError(Protocol::ErrorCodes::USER_OFFLINE));
        return false;
    }
    return true;
}

void Server::ServerCore::userCallUser(const std::string &client_id, Protocol::ProtocolData protocolData)
{
    auto p = (Protocol::CallUser *)protocolData.data.c_str();

    LOG.log("[CMD] USER CALL USER " + std::string(p->username));
    if (_indexUserServer.count(p->username) == 0)
    {
        LOG.warning("[CMD] [USER CALL USER] is offline");
        sendResponse(client_id, makeError(Protocol::ErrorCodes::USER_REJECTED_CALL));
        return;
    }

    if (_users[p->username].incall == true)
    {
        LOG.warning("[CMD] [USER CALL USER] already in call");
        sendResponse(client_id, makeError(Protocol::ErrorCodes::USER_REJECTED_CALL));
        return;
    }

    struct Protocol::UserCallYou call;
    Protocol::ProtocolData data = makePacket(Protocol::ServerToClient::USER_CALL_YOU);
    data.header.data_size = sizeof(struct Protocol::UserCallYou);

    std::memset(call.caller,  0, 32);
    std::string called = _indexIdUser[client_id] + "|" + _comm->getClientInfo(client_id).ip;
    size_t len = called.copy(call.caller, sizeof(call.caller) - 1);
    call.caller[len] = 0;

    std::memset(call.ip,  0, 32);
    std::string ip = _comm->getClientInfo(client_id).ip;
    len = ip.copy(call.ip, sizeof(call.ip) - 1);
    call.ip[len] = 0;

    LOG.warning("[CMD] [USER CALL] Giving ip: " + std::string(call.ip));

    data.data = std::string(reinterpret_cast<char *>(&call), sizeof(struct Protocol::UserCallYou));
    sendResponse(_indexUserServer[p->username], data);
}

void Server::ServerCore::userAcceptCall(const std::string &client_id, Protocol::ProtocolData protocolData)
{
    auto p = (Protocol::AcceptCallAndGivePort *)protocolData.data.c_str();

    LOG.log("[CMD] USER ACCEPT CALL " + std::string(p->username));
    if (_indexUserServer.count(p->username) == 0)
    {
        LOG.warning("[CMD] [USER CALL USER] is offline");
        sendResponse(client_id, makeError(Protocol::ErrorCodes::USER_REJECTED_CALL));
        return;
    }

    struct Protocol::UserAcceptedCall call{};
    Protocol::ProtocolData data = makePacket(Protocol::ServerToClient::USER_ACCEPTED_CALL);
    data.header.data_size = sizeof(struct Protocol::UserAcceptedCall);

    std::memset(call.ip, 0, 32);
    size_t len = _comm->getClientInfo(client_id).ip.copy(call.ip, (sizeof call.ip) - 1);
    call.ip[len] = 0;

    call.port = p->port;

    LOG.warning("[CMD] [USER ACCEPT CALL] Giving ip and port: " + std::string(call.ip) + " " + std::to_string(call.port));

    data.data = std::string(reinterpret_cast<char *>(&call), sizeof(struct Protocol::UserAcceptedCall));
    data.header.timestamp = p->port;
    sendResponse(_indexUserServer[p->username], data);
}

void Server::ServerCore::userDenyCall(const std::string &, Protocol::ProtocolData protocolData)
{
    auto p = (Protocol::RejectCall *)protocolData.data.c_str();

    LOG.log("[CMD] USER REJECT CALL " + std::string(p->username));
    sendResponse(_indexUserServer[p->username], makeError(Protocol::ErrorCodes::USER_REJECTED_CALL));
}
