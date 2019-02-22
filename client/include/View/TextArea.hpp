// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// TextArea.hpp created 04/10/17

#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include "IZone.hpp"
#include "Logger.hpp"

namespace View
{
    class TextArea : public IZone
    {
      private:
        std::string _name;
        QLineEdit _input;
        QFont _font;
        std::string _fontName;
        int _fontSize;
//        std::string _font = "Arial";

      public:
        TextArea(const std::string &name, QWidget *parent);
      public:
        ~TextArea() override;
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
        IZone &onAction(std::function<void()> function) override;
    };
}

