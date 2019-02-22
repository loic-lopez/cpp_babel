// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// IUser.hpp created 28/09/2017

#pragma once

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <string>
#include <vector>
#include <IServerCommunicator.hpp>
#include <ostream>
#include "data_structs.hpp"
#include "Chat.hpp"

namespace Server
{
    struct UserInfo
    {
        std::string id;
        std::string pseudo;
        std::string username;
        std::string password;
        std::string city;
        std::vector<std::string> friendList;
        bool incall;
        std::string ip;
        std::string lang;
        std::string motd;
        std::vector<std::string> pendingInvites;
        int phone;
        enum Protocol::Status status;
//        std::map<int, Chat> vecConversation;

        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int)
        {
            ar & boost::serialization::make_nvp("id", id);
            ar & boost::serialization::make_nvp("pseudo", pseudo);
            ar & boost::serialization::make_nvp("username", username);
            ar & boost::serialization::make_nvp("password", password);
            ar & boost::serialization::make_nvp("city", city);
            ar & boost::serialization::make_nvp("friendlist", friendList);
            ar & boost::serialization::make_nvp("incall", incall);
            ar & boost::serialization::make_nvp("ip", ip);
            ar & boost::serialization::make_nvp("lang", lang);
            ar & boost::serialization::make_nvp("motd", motd);
            ar & boost::serialization::make_nvp("pendingInvites", pendingInvites);
            ar & boost::serialization::make_nvp("phone", phone);
            ar & boost::serialization::make_nvp("status", status);
        }
    };
}