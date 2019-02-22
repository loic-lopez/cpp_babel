// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Chat.hpp created 28/09/2017

#pragma once

#include <map>
#include <vector>
#include "Message.hpp"

namespace Server
{
    class Chat
    {
      private:
        int id;
        std::map<int, struct Message> _conv;
        std::vector<std::string> _people;

      public:
        Chat();
        ~Chat();

        Chat &addMessage(const struct Message &);
        Chat &addUser(const std::string &);
        Chat &deleteConv();
        Chat &deleteMessage(int);
        Chat &deleteUSerFromChat(const std::string &);
        Chat &updateMessage(const struct Message &);

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            (void) version;
            ar & id;
            ar & _conv;
            ar & _people;
        }
    };
}