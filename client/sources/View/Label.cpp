// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Label.cpp created 03/10/17

#include "Label.hpp"

View::Label::Label(const std::string &name, QWidget *parent) :
    _label(parent)
{
    LOG.log("Creating LABEL " + name);

    _fontSize = 10;
    _fontName = "Arial";
    _font = QFont(_fontName.c_str(), _fontSize);

    _label.setObjectName(name.c_str());
    _name = name;
}

View::Label::~Label()
{
    LOG.log("Destroying zone " + _name);
    _label.close();
}

View::IZone &View::Label::hide()
{
    _label.hide();
    return *this;
}

View::IZone &View::Label::show()
{
    _label.show();
    return *this;
}

View::IZone &View::Label::font(std::string &path)
{
    _font = QFont(path.c_str(), _fontSize);
    _label.setFont(_font);
    return *this;
}

View::IZone &View::Label::place(int x, int y)
{
    int screenWidth = _label.parentWidget()->width();
    int screenHeight = _label.parentWidget()->height();

    _label.setGeometry((screenWidth * x) / 100, (screenHeight * y) / 100, _label.width(), _label.height());
    return *this;
}

View::IZone &View::Label::setSize(int w, int h)
{
    _label.setGeometry(_label.x(), _label.y(), w, h);
    return *this;
}

View::IZone &View::Label::setBackground(const std::string &string)
{
    return *this;
}

View::IZone &View::Label::setBorder(int size, const std::string &color)
{
    return *this;
}

View::IZone &View::Label::setImage(const std::string &path)
{
    LOG.fatal("Cant set Image on a Label");
    return *this;
}

View::IZone &View::Label::setText(const std::string &txt)
{
    _label.setText(txt.c_str());
    _label.setFont(_font);
    return *this;
}

View::IZone &View::Label::setTextColor(const std::string &color)
{
    std::string c = "color: " + color + ";";
    _label.setStyleSheet(c.c_str());
    return *this;
}

View::IZone &View::Label::setZ_index(int index)
{
    return *this;
}

std::string View::Label::getText()
{
    return _label.text().toStdString();
}

View::IZone &View::Label::onAction(std::function<void(void)> function)
{
    return *this;
}

View::IZone &View::Label::setTextSize(int size)
{
    _fontSize = size;
    _font = QFont(_fontName.c_str(), _fontSize);
    _label.setFont(_font);
    return *this;
}

bool View::Label::isShowed()
{
    return _label.isVisible();
}
