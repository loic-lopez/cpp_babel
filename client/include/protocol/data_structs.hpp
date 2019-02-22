// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// data_structs.hpp created 28/09/2017

#pragma once

#include <string>
#include <vector>

#include "codes.hpp"

namespace Protocol
{
    constexpr static int MAGIC_CODE_PACKET_HEADER = 0x1337;
    constexpr static int MAGIC_CODE_SOUND_PACKET = 0x42;
    constexpr static int MAGIC_CODE_VIDEO_PACKET = 0xAEEE;

    struct PacketHeader
    {
        int magiccode;
        int timestamp;
        char cmd;
        int data_size;
        char error;
    };

    struct SoundPacket
    {
        int magiccode;
        int timestamp;
        int size;
    };

    struct VideoPacket
    {
        int magiccode;
        int timestamp;
        int size;
        char *video_data;
    };

    constexpr int HEADER_SIZE = sizeof(struct PacketHeader);
    constexpr int SOUND_PACKET_SIZE = sizeof(struct SoundPacket);
    constexpr int VIDEO_PACKET_SIZE = sizeof(struct VideoPacket);

    struct Plugin
    {
        char name[32];
        char description[512];
    };

    enum Status
    {
        DISCONNECTED = 0,
        CONNECTED,
        BUSY,
        DONT_BOTHER,
        INVISIBLE
    };

    struct UserInfo
    {
        char username[32];
        char pseudo[32];
        enum Status status;
        char motd[512];
        char city[32];
        char phone[32];
        char mail[32];
        char langue[32];
    };

    struct GroupInfo
    {
        int id;
        char name[32];
        char usernames[10][32];
    };

    struct Message
    {
        int id;
        int timestamp;
        char message[1024];
        bool modified;
        char author[32];
        char user_id_to[32];
        int group_id;
    };
} // Namespace Protocol