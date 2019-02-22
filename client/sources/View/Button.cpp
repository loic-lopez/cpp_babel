// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Button.cpp created 03/10/17

#include "Button.hpp"

View::Button::Button(const std::string &name, QWidget *parent) :
    _button(parent)
{
    LOG.log("Creating BUTTON " + name);
    _name = name;

    _button.setObjectName(name.c_str());

    _fontSize = 10;
    _fontName = "Arial";
    _font = QFont(_fontName.c_str(), _fontSize);

    _button.connect(&_button, &QPushButton::clicked, [this] {
        _onAction();
    });
}

View::Button::~Button()
{
    LOG.log("Destroying zone " + _name);
    _button.close();
}

View::IZone &View::Button::hide()
{
    _button.hide();
    return *this;
}

View::IZone &View::Button::show()
{
    _button.show();
    return *this;
}

View::IZone &View::Button::font(std::string &path)
{
    _font = QFont(path.c_str(), _fontSize);
    _button.setFont(_font);
    return *this;
}

View::IZone &View::Button::place(int x, int y)
{
    int screenWidth = _button.parentWidget()->width();
    int screenHeight = _button.parentWidget()->height();

    _button.setGeometry((screenWidth * x) / 100, (screenHeight * y) / 100, _button.width(), _button.height());
    return *this;
}

View::IZone &View::Button::setSize(int w, int h)
{
    _button.setGeometry(_button.x(), _button.y(), w, h);
    return *this;
}

View::IZone &View::Button::setBackground(const std::string &string)
{
    return *this;
}

View::IZone &View::Button::setBorder(int size, const std::string &color)
{
    return *this;
}

View::IZone &View::Button::setImage(const std::string &path)
{
    return *this;
}

View::IZone &View::Button::setText(const std::string &txt)
{
    _button.setText(txt.c_str());
    _button.setFont(_font);
    return *this;
}

View::IZone &View::Button::setTextSize(int size)
{
    _fontSize = size;
    _font = QFont(_fontName.c_str(), _fontSize);
    _button.setFont(_font);
    return *this;
}

View::IZone &View::Button::setTextColor(const std::string &color)
{
    return *this;
}

View::IZone &View::Button::setZ_index(int index)
{
    return *this;
}

std::string View::Button::getText()
{
    return nullptr;
}

View::IZone &View::Button::onAction(std::function<void(void)> function)
{
    _onAction = function;
    return *this;
}

bool View::Button::isShowed()
{
    return _button.isVisible();
}
