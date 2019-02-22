#pragma once

#include <string>
#include <vector>

namespace View
{
    enum Action
    {
        MSG_SEND,
        MSG_EDIT,
        MSG_DELETE,
        CALL_CALL,
        CALL_HANG,
        LOGIN,
        LOGOUT,
        REGISTER,
        CHANGE_PWD,
        CHANGE_INFO,
        CHANGE_MSG_DAY,
        CHANGE_STATUS,
        FRIEND_REQUEST,
        FRIEND_DELETE,
        FRIEND_INFO,
        GROUP_ADD,
        GROUP_ADD_USER,
        GROUP_DELETE,
        GROUP_LEAVE,
        GROUP_CHANGE_PSEUDO,
        GROUP_INFO,
        GET_MSGS,
        LOAD_PLUGIN,
        VIDEO_CALL,
        MUTE,
        CUSTOM_PLUGIN
    };

    struct ActionData
    {
        enum Action action;
        std::vector<std::string> _data;
    };
}