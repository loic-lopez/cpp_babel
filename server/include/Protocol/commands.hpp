// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// commands.hpp created 28/09/2017

#pragma once

#include "data_structs.hpp"
#include "codes.hpp"

namespace Protocol
{
    struct AccountCreate
    {
        char username[32];
        char password[32];
    };

//#pragma pack(push, 1)
    struct AccountLogin
    {
        char username[32];
        char password[32];
    };
//#pragma pack(pop)

    struct AccountChangePassword
    {
        char password[32];
        char new_password[32];
    };

    struct AccountChangePseudo
    {
        char new_pseudo[32];
    };

    struct AccountChangeStatus
    {
        enum Status status;
    };

    struct AccountChangeMOTD
    {
        char motd[512];
    };

    struct AccountChangeInfo
    {
        struct UserInfo info;
    };

    struct UserAddContact
    {
        char username[32];
    };

    struct UserAcceptContact
    {
        char username[32];
    };

    struct UserDenyContact
    {
        char username[32];
    };

    struct UserDeleteContact
    {
        char username[32];
    };

    struct UserGetInfoOf
    {
        char username[32];
    };

    struct GroupeCreate
    {
        char username[32]; //We add then peoples one by one
    };

    struct GroupRename
    {
        int id;
        char name[64];
    };

    struct GroupAddUser
    {
        char username[32];
    };

    struct GroupDeleteUser
    {
        char username[32];
    };

    struct GroupDelete
    {
        int id;
    };

    struct MsgGetUser
    {
        char username[32];
        int from_id;
        int nb_msg;
    };

    struct MsgGetGroup
    {
        char username[32];
        int from_id;
        int nb_msg;
    };

    struct MsgTo
    {
        struct Message msg;
    };

    struct MsgDelete
    {
        int id;
    };

    struct CallUser
    {
        char username[32];
    };

    struct CallGroup
    {
        int group_id;
    };

    struct AcceptCallAndGivePort
    {
        char username[32];
        int port;
    };

    struct RejectCall
    {
        char username[32];
    };

    struct PluginSendMsgToServer
    {
        char plugin_name[32];
        int length;
        char *data;
    };


    // Server To Client

    struct SendFriendList
    {
        char fri[32];
    };

    struct SendUserInfo
    {
        struct UserInfo info;
    };

    struct UserCallYou
    {
        char caller[32];
        char ip[32];
    };

    struct UserAcceptedCall
    {
        char ip[32];
        int port;
    };

    struct UserHasSentMsg
    {
        struct Message msg;
    };

    struct UserHasSentFriendRequest
    {
        char username[32];
    };

    struct UserHasAcceptedFriendRequest
    {
        struct UserInfo info;
    };

    struct UserHasChangeStatus
    {
        char username[32];
        struct UserInfo;
    };

    struct UserHasChangePseudo
    {
        char username[32];
        char pseudo[32];
    };

    struct SendGroupList
    {
        int id[10][32];
    };

    struct SendGroupInfo
    {
        struct GroupInfo info;
    };

    struct GroupRemoved
    {
        int group_id;
    };

    struct SendHistoryMsg
    {
        struct Message msgs[10];
    };

    struct PluginMsgToUser
    {
        char pluginName[32];
        char *data;
    };
} // Namespace Protocol