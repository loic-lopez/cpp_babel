#pragma once

#include "IWindow.hpp"
#include "Action.hpp"

namespace View
{
    class IGraphics
    {
      public:
        virtual ~IGraphics()
        {
        }

        virtual IWindow &createWindow(const std::string &name) =0;
        virtual IGraphics &closeWindow(const std::string &name) =0;
        virtual IGraphics &getEvent() =0;
        virtual IGraphics &switchToWindow(const std::string &name) =0;
        virtual IWindow &getWindow(const std::string &name) = 0;
        virtual IGraphics &run() = 0;
        virtual IGraphics &stop() = 0;
        virtual IGraphics &onAction(std::function<void (void)>) = 0;
        virtual IGraphics &deleteWindow(const std::string &name) = 0;
        virtual bool doesWindowExist(const std::string &name) = 0;
        virtual IGraphics &closeAllWindow() = 0;
    };
}