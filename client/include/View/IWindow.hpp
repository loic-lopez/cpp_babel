#pragma once

#include "ZoneType.hpp"
#include "IZone.hpp"
#include <string>

namespace View
{
    class IWindow
    {
      public:
        virtual ~IWindow()
        {
        }

        virtual IZone &createZone(const std::string &name, enum ZoneType) =0;
        virtual IWindow &hide() = 0;
        virtual IWindow &show() = 0;
        virtual IZone &getZone(const std::string &name) =0;
        virtual IWindow &setTitle(const std::string &name) = 0;
        virtual IWindow &setSize(int width, int height) = 0;
        virtual IWindow &setFocus() = 0;
        virtual IWindow &setMinSize(int width, int height) = 0;
        virtual IWindow &setMaxSize(int width, int height) = 0;
        virtual std::pair<int, int> getSize() = 0;
        virtual IWindow &loadCSS(const std::string &path) = 0;


        virtual IWindow &onAction(std::function<void (void)>) = 0;
    };
}