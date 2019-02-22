// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// TextArea.cpp created 04/10/17

#include "TextArea.hpp"

View::TextArea::TextArea(const std::string &name, QWidget *parent) :
    _input(parent)
{
    _name = name;
    _input.setObjectName(name.c_str());
    _fontSize = 10;
    _fontName = "Arial";
    _font = QFont(_fontName.c_str(), _fontSize);
    if (name.find("password") != std::string::npos)
    {
        _input.setEchoMode(QLineEdit::Password);
        _input.setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);
    }
    LOG.log("Creating TextArea " + name);
}

View::TextArea::~TextArea()
{
}

View::IZone &View::TextArea::hide()
{
    _input.hide();
    return *this;
}

View::IZone &View::TextArea::show()
{
    _input.show();
    return *this;
}

bool View::TextArea::isShowed()
{
    return _input.isVisible();
}

View::IZone &View::TextArea::font(std::string &path)
{
    _font = QFont(path.c_str(), _fontSize);
    _input.setFont(_font);
    return *this;
}

View::IZone &View::TextArea::place(int x, int y)
{
    int screenWidth = _input.parentWidget()->width();
    int screenHeight = _input.parentWidget()->height();

    _input.setGeometry((screenWidth * x) / 100, (screenHeight * y) / 100, _input.width(), _input.height());
    return *this;
}

View::IZone &View::TextArea::setSize(int w, int h)
{
    _input.setGeometry(_input.x(), _input.y(), w, h);
    return *this;
}

View::IZone &View::TextArea::setBackground(const std::string &string)
{
    return *this;
}

View::IZone &View::TextArea::setBorder(int size, const std::string &color)
{
    return *this;
}

View::IZone &View::TextArea::setImage(const std::string &path)
{
    LOG.fatal("Cant set Image on a Button");
    return *this;
}

View::IZone &View::TextArea::setText(const std::string &txt)
{
    _input.setPlaceholderText(txt.c_str());
    _input.setFont(_font);
    return *this;
}

View::IZone &View::TextArea::setTextSize(int size)
{
    _fontSize = size;
    _font = QFont(_fontName.c_str(), _fontSize);
    _input.setFont(_font);
    return *this;
}

View::IZone &View::TextArea::setTextColor(const std::string &color)
{
    return *this;
}

View::IZone &View::TextArea::setZ_index(int index)
{
    return *this;
}

std::string View::TextArea::getText()
{
    return _input.text().toStdString();
}

View::IZone &View::TextArea::onAction(std::function<void()> function)
{
    return *this;
}