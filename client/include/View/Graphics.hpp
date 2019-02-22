#pragma once

#include <unordered_map>
//#include <QtWidgets/QApplication>
#include "IGraphics.hpp"
#include "Logger.hpp"
#include "Window.hpp"

namespace View
{
    class Graphics : public IGraphics
    {
      private:
//        QApplication _app;
        std::unordered_map<std::string, IWindow *> _windows;

        std::function<void(void)> _onAction;

      public:

        ~Graphics() override;
        Graphics();
        IWindow &createWindow(const std::string &name) override;
        IGraphics &closeWindow(const std::string &name) override;
        IGraphics &getEvent() override;
        IGraphics &switchToWindow(const std::string &name) override;
        IWindow &getWindow(const std::string &name) override;
        IGraphics &run() override;
        IGraphics &stop() override;
        IGraphics &onAction(std::function<void(void)> function) override;
        IGraphics &deleteWindow(const std::string &name) override;
        bool doesWindowExist(const std::string &name) override;
        IGraphics &closeAllWindow() override;
    };
}