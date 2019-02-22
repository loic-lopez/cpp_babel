// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// ConvInfo.hpp created 28/09/2017

#pragma once

#include <string>
#include "Chat.hpp"

namespace Server
{
    class ConvInfo
    {
      private:
        std::map<int, Chat> _indexMP; //(username le plus bas dans l'alphabet + autre username + sha())
        std::map<int, Chat> _indexGroup;

      public:
        ConvInfo();
        virtual ~ConvInfo();

        Chat &getMP(int);
        Chat &getGroupConv(int);

        ConvInfo &addConvMP(int, Chat);
        ConvInfo &addGroupMP(int, Chat);
        ConvInfo &deleteConv();
    };
}
