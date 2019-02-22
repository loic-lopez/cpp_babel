#include "Window.hpp"

View::Window::Window(const std::string &name) :
    _name(name)
{
    LOG.log("Creating window " + name);
    _win.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    _win.setWindowTitle(name.c_str());
    _win.move(200, 50);
}

View::Window::~Window()
{
    LOG.log("Destroying window " + _name);
    for (auto &it : _zones) {
        delete (it.second);
    }
}

View::IZone &View::Window::createZone(const std::string &name, View::ZoneType type)
{
    if (_zones.count(name) != 0)
    {
        LOG.warning("Zone " + name + " already exist");
        delete(_zones[name]);
    }
    switch (type) {
        case TEXT:
            _zones[name] = new Label(name, &_win);
            break;
        case PICTURE:
            LOG.fatal("not yet implemented");
            break;
        case DRAWING_ZONE:
            LOG.fatal("not yet implemented");
            break;
        case BUTTON:
            _zones[name] = new Button(name, &_win);
            break;
        case INPUT_BOX:
            _zones[name] = new TextArea(name, &_win);
            break;
        case TEXT_BOX:
            _zones[name] = new TextBoxArea(name, &_win);
            break;
    }
    return *_zones[name];
}

View::IZone &View::Window::getZone(const std::string &name)
{
    if (_zones.count(name) == 0)
        LOG.fatal("Zone " + name + " doesnt exist");
    return *_zones[name];
}

View::IWindow &View::Window::setTitle(const std::string &name)
{
    _win.setWindowTitle(QString(name.c_str()));
    return *this;
}

View::IWindow &View::Window::setSize(int width, int height)
{
    _win.resize(width, height);
    return *this;
}

std::pair<int, int> View::Window::getSize()
{
    std::pair<int, int> size = std::make_pair(_win.width(), _win.height());
    return size;
}

View::IWindow &View::Window::onAction(std::function<void(void)> function)
{
    _onAction = function;
    return *this;
}

View::IWindow &View::Window::hide()
{
    _win.hide();
    return *this;
}

View::IWindow &View::Window::show()
{
    _win.show();
    return *this;
}

View::IWindow &View::Window::loadCSS(const std::string &path)
{
    QFile file(path.c_str());
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    _win.setStyleSheet(styleSheet);

    return *this;
}

View::IWindow &View::Window::setMinSize(int width, int height)
{
    _win.setMinimumSize(width, height);
    return *this;
}

View::IWindow &View::Window::setMaxSize(int width, int height)
{
    _win.setMaximumSize(width, height);
    return *this;
}

View::IWindow &View::Window::setFocus()
{
    _win.activateWindow();
    return *this;
}