// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// SendCMD.cpp created 07/10/17

#include "ClientCore.hpp"


Controller::IClient &Controller::ClientCore::sendLoginCMD(std::string &login, std::string &password)
{
    auto proto = makePacket(Protocol::ACCOUNT_LOGIN);

    Protocol::AccountLogin packet_login;

    std::memset(packet_login.username, 0, 32);
    std::memset(packet_login.password, 0, 32);

    size_t len = login.copy(packet_login.username, (sizeof packet_login.username) - 1);
    packet_login.username[len] = 0;

    len = password.copy(packet_login.password, (sizeof packet_login.password) - 1);
    packet_login.password[len] = 0;

    proto.data = std::string(reinterpret_cast<char *>(&packet_login), sizeof(struct Protocol::AccountLogin));
    proto.header.data_size = sizeof(struct Protocol::AccountLogin);

//    NETSendQT(proto);
    _network->Send(proto);
    return *this;
}

Controller::IClient &Controller::ClientCore::sendRegisterCMD(std::string &login, std::string &password)
{
    auto proto = makePacket(Protocol::ACCOUNT_CREATE);

    Protocol::AccountLogin packet_register;

    std::memset(packet_register.username, 0, 32);
    std::memset(packet_register.password, 0, 32);

    size_t len = login.copy(packet_register.username, (sizeof packet_register.username) - 1);
    packet_register.username[len] = 0;

    len = password.copy(packet_register.password, (sizeof packet_register.password) - 1);
    packet_register.password[len] = 0;

    proto.data = std::string(reinterpret_cast<char *>(&packet_register), sizeof(struct Protocol::AccountCreate));
    proto.header.data_size = sizeof(struct Protocol::AccountCreate);

    _network->Send(proto);
    return *this;
}


Controller::IClient &Controller::ClientCore::sendNeedFriendList()
{
    Protocol::ProtocolData packet = makePacket(Protocol::ClientToServer::USER_GET_ALL_FRIENDS);

    packet.header.data_size = 0;

    _onReceiveFriendList = [&] (Protocol::ProtocolData data) {
        receiveFriendList(data);
    };
    _network->Send(packet);
    return *this;
}

Controller::IClient &Controller::ClientCore::sendFriendRequest(const std::string &username)
{
    Protocol::ProtocolData packet = makePacket(Protocol::ClientToServer::USER_ADD_CONTACT);
    Protocol::UserAddContact ac;

    std::memset(ac.username, 0, 32);
    size_t len = username.copy(ac.username, (sizeof ac.username) - 1);
    ac.username[len] = 0;

    packet.data = std::string(reinterpret_cast<char *>(&ac), sizeof(struct Protocol::UserAddContact));

    packet.header.data_size = sizeof(struct Protocol::UserAddContact);
    _network->Send(packet);
    return *this;
}


Controller::IClient &Controller::ClientCore::callFriend(const std::string &username)
{
    auto paquet = makePacket(Protocol::ClientToServer::CALL_USER);
    Protocol::CallUser data;

    std::memset(data.username, 0, 32);
    size_t len = username.copy(data.username, (sizeof data.username) - 1);
    data.username[len] = 0;

    paquet.data = std::string(reinterpret_cast<char *>(&data), sizeof(struct Protocol::CallUser));
    paquet.header.data_size = sizeof(struct Protocol::CallUser);
    _caller = username;
    _network->Send(paquet);
    return *this;
}

void Controller::ClientCore::acceptCallFrom(std::string from, int port)
{
    auto paquet = makePacket(Protocol::ClientToServer::CALL_ACCEPT);
    Protocol::AcceptCallAndGivePort data;

    std::memset(data.username, 0, 32);
    size_t len = from.copy(data.username, (sizeof data.username) - 1);
    data.username[len] = 0;
    data.port = port;

    paquet.data = std::string(reinterpret_cast<char *>(&data), sizeof(struct Protocol::AcceptCallAndGivePort));
    paquet.header.data_size = sizeof(struct Protocol::AcceptCallAndGivePort);
    _network->Send(paquet);
}

void Controller::ClientCore::denyCallFrom(std::string from)
{
    auto paquet = makePacket(Protocol::ClientToServer::CALL_DENY);
    Protocol::RejectCall data;

    std::memset(data.username, 0, 32);
    size_t len = from.copy(data.username, (sizeof data.username) - 1);
    data.username[len] = 0;

    paquet.data = std::string(reinterpret_cast<char *>(&data), sizeof(struct Protocol::RejectCall));
    paquet.header.data_size = sizeof(struct Protocol::RejectCall);
    _network->Send(paquet);
}