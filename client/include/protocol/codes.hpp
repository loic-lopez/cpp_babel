// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// codes.hpp created 28/09/2017

#pragma once

namespace Protocol
{
    enum ErrorCodes : char
    {
        OK = 0,
        INCORRECT_LOGIN_OR_PASSWORD_FORMAT = 1,
        BAD_PASSWORD_OR_LOGIN = 2,
        USER_ALREADY_EXIST = 20,
        USER_DONT_EXIST = 21,
        USER_OFFLINE = 22,
        USER_ALREADY_IN_GROUP = 23,
        USER_ALREADY_YOUR_FRIEND = 24,
        USER_REJECTED_CALL = 25,
        GROUP_DONT_EXIST = 40,
        MESSAGE_DONT_EXIST = 60,
        CANT_MESSAGE_YOURSELF = 61,
        CANT_MODIFY_ANOTHER_USER_MESSAGE = 62,
        CANT_CALL_YOURSELF = 80,
        USER_ALREADY_IN_CALL = 81,
        UNKNOWN_ERROR = 100,
        BAD_COMMAND = 101
    };

    enum ClientToClient : char
    {
        AUDIO = 0,
        VIDEO = 1,
    };

    enum ClientToServer : char
    {
        ACCOUNT_CREATE = 0,
        ACCOUNT_LOGIN = 1,
        ACCOUNT_CHANGE_PASS = 2,
        ACCOUNT_DELETE = 3,
        ACCOUNT_CHANGE_PSEUDO = 4,
        ACCOUNT_CHANGE_STATUS = 5,
        ACCOUNT_CHANGE_MOTD = 6,
        ACCOUNT_CHANGE_INFO = 7,
        USER_GET_ALL_FRIENDS = 20,
        USER_ADD_CONTACT = 21,
        USER_ACCEPT_CONTACT = 22,
        USER_DENY_CONTACT = 23,
        USER_DELETE_CONTACT = 24,
        USER_GET_INFO_OF = 25,
        USER_GET_PENDING_INVITES = 26,
        GROUP_CREATE = 40,
        GROUP_GET_LIST = 41,
        GROUP_ADD_USER = 42,
        GROUP_DELETE_USER = 43,
        GROUP_RENAME = 44,
        GROUP_DELETE = 45,
        GROUP_INFO = 46,
        MSG_GET_USER = 60,
        MSG_GET_GROUP = 61,
        MSG_DELETE = 62,
        MSG_TO = 63,
        CALL_USER = 80,
        CALL_GROUP = 81,
        CALL_HANG = 82,
        CALL_ACCEPT = 83,
        CALL_DENY = 84,
        PLUGIN_SEND_MSG_TO_SERVER = 100,
    };

    enum ServerToClient : char
    {
        USER_CALL_YOU = 0,
        USER_ACCEPTED_CALL = 1,
        USER_HANGED_CALL = 3,
        USER_SEND_MSG = 4,
        USER_HAS_SENT_FRIEND_REQUEST = 5,
        USER_HAS_ACCEPTED_FRIEND = 6,
        USER_HAS_CHANGE_STATUS = 7,
        USER_HAS_CHANGE_PSEUDO = 8,
        SEND_USER_LIST = 20,
        SEND_USER_INFO = 21,
        SEND_GROUP_INFO = 22,
        SEND_GROUP_LIST = 23,
        SEND_HISTORY_MSG = 24,
        GROUP_DELETED = 40,
        PLUGIN_MSG = 60,
        ERROR = 80
    };
} // Namespace Protocol