#pragma once

#include <string>
#include <vector>

namespace Plugin
{
    struct PluginReturn
    {
        std::string plugin_name;
        std::string username;
        int size;
        char *data;
    };

    class IPlugin
    {
      public:
        virtual std::vector<struct PluginReturn> execute(/* TODO USER */);
    };
}