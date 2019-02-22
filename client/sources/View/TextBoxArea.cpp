// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// TextBoxArea.cpp created 04/10/17

#include "TextBoxArea.hpp"

View::TextBoxArea::TextBoxArea(const std::string &name, QWidget *parent) :
    _input(parent)
{
    _name = name;
    _input.setObjectName(name.c_str());
    _input.setReadOnly(true);
    _input.setFocusPolicy(Qt::NoFocus);
    _fontSize = 10;
    _fontName = "Arial";
    _font = QFont(_fontName.c_str(), _fontSize);
    LOG.log("Creating TextBoxArea " + name);
}

View::TextBoxArea::~TextBoxArea()
{
}

View::IZone &View::TextBoxArea::hide()
{
    _input.hide();
    return *this;
}

View::IZone &View::TextBoxArea::show()
{
    _input.show();
    return *this;
}

bool View::TextBoxArea::isShowed()
{
    return _input.isVisible();
}

View::IZone &View::TextBoxArea::font(std::string &path)
{
    _font = QFont(path.c_str(), _fontSize);
    _input.setFont(_font);
    return *this;
}

View::IZone &View::TextBoxArea::place(int x, int y)
{
    int screenWidth = _input.parentWidget()->width();
    int screenHeight = _input.parentWidget()->height();

    _input.setGeometry((screenWidth * x) / 100, (screenHeight * y) / 100, _input.width(), _input.height());
    return *this;
}

View::IZone &View::TextBoxArea::setSize(int w, int h)
{
    _input.setGeometry(_input.x(), _input.y(), w, h);
    return *this;
}

View::IZone &View::TextBoxArea::setBackground(const std::string &string)
{
    return *this;
}

View::IZone &View::TextBoxArea::setBorder(int size, const std::string &color)
{
    return *this;
}

View::IZone &View::TextBoxArea::setImage(const std::string &path)
{
    LOG.fatal("Cant set Image on a Button");
    return *this;
}

View::IZone &View::TextBoxArea::setText(const std::string &txt)
{
    _input.setPlaceholderText(txt.c_str());
    _input.setFont(_font);
    return *this;
}

View::IZone &View::TextBoxArea::setTextSize(int size)
{
    _fontSize = size;
    _font = QFont(_fontName.c_str(), _fontSize);
    _input.setFont(_font);
    return *this;
}

View::IZone &View::TextBoxArea::setTextColor(const std::string &color)
{
    return *this;
}

View::IZone &View::TextBoxArea::setZ_index(int index)
{

    return *this;
}

std::string View::TextBoxArea::getText()
{
    return _input.toPlainText().toStdString();
}

View::IZone &View::TextBoxArea::onAction(std::function<void()> function)
{
    return *this;
}