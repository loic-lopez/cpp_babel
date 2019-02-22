// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Chat.hpp created 07/10/17

#pragma once

#pragma once

#include <map>
#include <vector>
#include "Message.hpp"

namespace Controller
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
    };
}