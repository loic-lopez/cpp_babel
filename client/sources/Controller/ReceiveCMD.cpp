// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// ReceiveCMDError.cpp created 07/10/17

#include "ClientCore.hpp"

Controller::IClient &Controller::ClientCore::processServerEvent(Protocol::ProtocolData data)
{
    LOG.warning("[CORE] Received command: " + std::to_string(data.header.cmd));
    if (data.header.cmd == Protocol::ServerToClient::ERROR)
    {
        switch (data.header.error) {
            default:
                errorWindow("Unknown error");
                break;
            case Protocol::ErrorCodes::BAD_COMMAND:
                LOG.error("Bad command sent");
                errorWindow("Bad command sent");
                break;
            case Protocol::ErrorCodes::OK:
                _onReceiveOk();
                break;
            case Protocol::ErrorCodes::BAD_PASSWORD_OR_LOGIN:
                _onReceiveIncorrectLogin();
                break;
            case Protocol::ErrorCodes::USER_DONT_EXIST:
                _onReceiveUserDontExist();
                break;
            case Protocol::ErrorCodes::USER_ALREADY_EXIST:
                _onReceiveUserAlreadyExist();
                break;
            case Protocol::ErrorCodes::USER_ALREADY_YOUR_FRIEND:
                _onReceiveUserAlreadyYourFriend();
                break;
            case Protocol::ErrorCodes ::USER_REJECTED_CALL:
                errorWindow("User rejected call");
                break;
        }
    }
    else
        switch (data.header.cmd)
        {
            default:
                errorWindow("Unknow error");
                break;
            case Protocol::ServerToClient::SEND_USER_LIST:
                receiveFriendList(data);
                break;
            case Protocol::ServerToClient::USER_HAS_SENT_FRIEND_REQUEST:
                receiveFriendRequest(data);
                break;
            case Protocol::ServerToClient::USER_HAS_ACCEPTED_FRIEND:
                [&] () { successWindow("You have a new friend !"); };
                break;
            case Protocol::ServerToClient::USER_CALL_YOU:
                receiveCallRequest(data);
                break;
            case Protocol::ServerToClient::USER_ACCEPTED_CALL:
                receiveCallAccept(data);
                break;
        }
}

Controller::IClient &Controller::ClientCore::loginProcess(const std::string &username, const std::string &password)
{
    _user.username = username;
    _user.password = password;
    _user.status = Protocol::Status::CONNECTED;
}


Controller::IClient &Controller::ClientCore::receiveFriendList(Protocol::ProtocolData data)
{
    if (_graphics->doesWindowExist("Friends"))
        _graphics->deleteWindow("Friends");

    _graphics->createWindow("Friends").setMinSize(200, 700).setSize(200, 700);

    std::string bro;
    Protocol::SendFriendList *list;
    list = (struct Protocol::SendFriendList *)data.data.c_str();

    std::string my_friend(list->fri);
    LOG.log("Found friend " + my_friend);
    if (_user.friendList.count(my_friend) == 0)
    {
        _user.friendList[my_friend] = {};
        _user.friendList[my_friend].username = my_friend;
    }

    View::IWindow &window = _graphics->getWindow("Friends");
    int i = 0;

    for (const auto &it : _user.friendList)
    {
        window.createZone(it.first + "_zone_friend", View::BUTTON).setSize(200,100).setText(it.first).setTextSize(20).place(0, i).onAction([&] () {
            LOG.warning("[CMD] Try to call " + it.first);
            callFriend(it.first);
        });
        i += 10;
    }
    window.show();
    return *this;
}

void Controller::ClientCore::receiveFriendRequest(Protocol::ProtocolData data)
{
    auto r = (Protocol::UserHasSentFriendRequest *)data.data.c_str();
    std::string bro(r->username);
    std::string broWindowName = bro + " friend request";
    this->_bro = bro;

        LOG.warning("ADDED YOU TO FRIEND REQUEST" + bro);
    _graphics->createWindow(broWindowName).setMinSize(200,200).setSize(400,200).createZone("accept-" + bro + "-label", View::TEXT).setText(bro + " want to be your friend").setTextSize(14).setSize(400,100).place(5,5);
    _graphics->getWindow(broWindowName).createZone("YESaccept-" + bro + "-button", View::BUTTON).setText("Y").setTextSize(60).setSize(200,100).place(0, 50).onAction([&, bro]() {

        auto packetYES = makePacket(Protocol::ClientToServer::USER_ACCEPT_CONTACT);
        Protocol::UserAcceptContact infoYES;
        packetYES.header.data_size = sizeof(struct Protocol::UserAcceptContact);

        std::memset(infoYES.username, 0, 32);
        size_t len = _bro.copy(infoYES.username, (sizeof infoYES.username) - 1);
        infoYES.username[len] = 0;

        packetYES.data = std::string(reinterpret_cast<char *>(&infoYES), sizeof(struct Protocol::UserAcceptContact));
        _network->Send(packetYES);
        _graphics->deleteWindow(_bro + " friend request");

        _user.friendList[_bro] = {};
        _user.friendList[_bro].username = _bro;
    });
    _graphics->getWindow(broWindowName).createZone("NOaccept-" + bro + "-button", View::BUTTON).setText("X").setTextSize(60).setSize(200,100).place(50, 50).onAction([&, bro] () {

        auto packetNO = makePacket(Protocol::ClientToServer::USER_DENY_CONTACT);
        Protocol::UserDenyContact infoNO;
        packetNO.header.data_size = sizeof(struct Protocol::UserDenyContact);

        std::memset(infoNO.username, 0, 32);
        auto len = _bro.copy(infoNO.username, (sizeof infoNO.username) - 1);
        infoNO.username[len] = 0;

        packetNO.data = std::string(reinterpret_cast<char *>(&infoNO), sizeof(struct Protocol::UserDenyContact));
        _network->Send(packetNO);
        _graphics->deleteWindow(_bro + " friend request");
    });
    _graphics->getWindow(broWindowName).show();
}

void Controller::ClientCore::receiveCallRequest(Protocol::ProtocolData data)
{
    auto user = (struct Protocol::UserCallYou *)data.data.c_str();

    _caller = std::string(user->caller);
    auto sp = _caller.find("|");
    _ip_other = _caller.substr(sp + 1, _caller.size());
    _caller = _caller.substr(0, sp);

    LOG.warning("[CMD] " + _caller + " is calling you from " + _ip_other);
    std::cout << _ip_other << std::endl;
    std::cout << std::to_string(data.header.data_size) << std::endl;

    callByFriendWindow(_caller);
}

void Controller::ClientCore::receiveCallAccept(Protocol::ProtocolData data)
{
    Protocol::UserAcceptedCall *user;
    user = (struct Protocol::UserAcceptedCall *)data.data.c_str();
    LOG.warning("[CMD] " + std::string(user->ip) + " accepted call on port " + std::to_string(data.header.timestamp));
    _ip_other = user->ip;
    _port_other = data.header.timestamp;
    HostSecond(_ip_other, DEFAULT_PORT_HOST_UDP);
    callWindow(_caller);
//    connectAndSendUDP(std::string(user->ip), user->port);
//    hostAndListenUDP(user->port + 1);
}