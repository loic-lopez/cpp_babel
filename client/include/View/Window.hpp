#pragma once

#include <unordered_map>
#include <QtWidgets/QWidget>
#include "IWindow.hpp"
#include "Graphics.hpp"
#include "Logger.hpp"
#include "Label.hpp"
#include <QtCore/QFile>
#include "Button.hpp"
#include "TextArea.hpp"
#include "TextBoxArea.hpp"
#include <QStyle>
#include <QDesktopWidget>

namespace View
{
    class Window : public IWindow
    {
      private:
        std::string _name;
        std::unordered_map<std::string, IZone *> _zones;
        QWidget _win;

        std::function<void(void)> _onAction;

      public:
        Window(const std::string &name);
        IWindow &hide() override;
        IWindow &show() override;
        ~Window() override;
        IZone &createZone(const std::string &name, ZoneType type) override;
        IZone &getZone(const std::string &name) override;
        IWindow &setTitle(const std::string &name) override;
        IWindow &setFocus() override;
        IWindow &setSize(int width, int height) override;
        IWindow &setMinSize(int width, int height) override;
        IWindow &setMaxSize(int width, int height) override;
        std::pair<int, int> getSize() override;
        IWindow &loadCSS(const std::string &path) override;

        IWindow &onAction(std::function<void(void)> function) override;
    };
}