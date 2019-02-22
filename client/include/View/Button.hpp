// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Button.hpp created 03/10/17

#pragma once

#include <QtWidgets/QPushButton>
#include <QDesktopWidget>
#include "IZone.hpp"
#include "Logger.hpp"

namespace View
{
    class Button : public IZone
    {
      private:
        std::string _name;
        QPushButton _button;
        QFont _font;
        std::string _fontName;
        int _fontSize;

        std::function<void(void)> _onAction;

      public:
        Button(const std::string &name, QWidget *parent);
        ~Button() override;
        IZone &hide() override;
        IZone &show() override;
        bool isShowed() override;
        IZone &font(std::string &path) override;
        IZone &place(int x, int y) override;
        IZone &setSize(int w, int h) override;
        IZone &setBackground(const std::string &string) override;
        IZone &setBorder(int size, const std::string &color) override;
        IZone &setImage(const std::string &path) override;
        IZone &setText(const std::string &txt) override;
        IZone &setTextSize(int size) override;
        IZone &setTextColor(const std::string &color) override;
        IZone &setZ_index(int index) override;
        std::string getText() override;
        IZone &onAction(std::function<void(void)> function) override;
    };
}

