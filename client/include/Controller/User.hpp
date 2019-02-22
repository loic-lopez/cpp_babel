// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// IUser.hpp created 28/09/2017

#pragma once

#include <string>
#include <vector>
#include "data_structs.hpp"
#include "Chat.hpp"

namespace Controller
{
    struct UserInfo
    {
        std::string pseudo;
        std::string username;
        std::string password;
        std::string city;
        std::map<std::string, struct UserInfo> friendList;
        bool incall;
        std::string ip;
        std::string lang;
        std::string motd;
        std::vector<std::string> pendingInvites;
        int phone;
        enum Protocol::Status status;
    };
}