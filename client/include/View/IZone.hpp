#pragma once

#include "ZoneType.hpp"
#include "Action.hpp"
#include <string>
#include <functional>

namespace View
{
    class IZone
    {
      public:
        virtual ~IZone()
        {
        }


        virtual IZone &hide() = 0;
        virtual IZone &show() = 0;
        virtual bool isShowed() = 0;
        virtual IZone &font(std::string &path) =0;
        virtual IZone &place(int x, int y) =0;
        virtual IZone &setSize(int w, int h) =0;
        virtual IZone &setBackground(const std::string &) =0;
        virtual IZone &setBorder(int size, const std::string &color) =0;
        virtual IZone &setImage(const std::string &path) =0;
        virtual IZone &setText(const std::string &txt) =0;
        virtual IZone &setTextSize(int size) = 0;
        virtual IZone &setTextColor(const std::string &color) =0;
        virtual IZone &setZ_index(int index) =0;
        virtual std::string getText() = 0;
        virtual IZone &onAction(std::function<void (void)>) = 0;
    };
}