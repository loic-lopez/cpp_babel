// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Label.hpp created 03/10/17

#pragma once

#include <QtWidgets/QLabel>
#include "IZone.hpp"
#include "Logger.hpp"

namespace View
{
    class Label : public IZone
    {
      private:
        std::string _name;
        QLabel _label;
        QFont _font;
        std::string _fontName;
        int _fontSize;

      public:
        Label(const std::string &name, QWidget *parent);
        ~Label() override;
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

