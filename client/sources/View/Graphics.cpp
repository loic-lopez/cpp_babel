#include "Graphics.hpp"

View::Graphics::Graphics()
//    _app(*new int, nullptr)
{}

View::Graphics::~Graphics()
{
    stop();
}

View::IWindow &View::Graphics::createWindow(const std::string &name)
{
    LOG.log("Creating new window " + name);
    if (name == "Babel Skype - Error" && _windows.count(name) != 0)
        closeWindow("Babel Skype - Error");
    if (_windows.count(name) != 0)
        LOG.error("Window " + name + " already exist !");
    _windows[name] = new Window(name);
    return *_windows[name];
}

View::IGraphics &View::Graphics::closeWindow(const std::string &name)
{
    LOG.log("Closing window " + name);
    if (_windows.count(name) == 0)
    {
        LOG.error("Window " + name + " don't exist while attempting to delete it");
        return *this;
    }
    else
        _windows[name]->hide();
//    delete (_windows[name]);
//    _windows.erase(name);
    return *this;
}

View::IGraphics &View::Graphics::getEvent()
{
    return *this;
}

View::IGraphics &View::Graphics::switchToWindow(const std::string &name)
{
    if (_windows.count(name) == 0)
        LOG.error("Window " + name + " don't exist while attempting to set focus");
    else
        _windows[name]->setFocus();
    return *this;
}

View::IWindow &View::Graphics::getWindow(const std::string &name)
{ ;
    if (_windows.count(name) == 0)
        LOG.fatal("Window " + name + " don't exist while attempting to get it");
    return *_windows[name];
}

View::IGraphics &View::Graphics::run()
{
    LOG.log("Running QT Graphic");
//    _app.exec();
    return *this;
}

View::IGraphics &View::Graphics::stop()
{
    LOG.log("Ending QT Graphic");
    exit(0);
//    for (auto &it : _windows)
//        it.second
//        delete(it.second);

    return *this;
}

View::IGraphics &View::Graphics::onAction(std::function<void(void)> function)
{
    _onAction = function;
    return *this;
}

View::IGraphics &View::Graphics::deleteWindow(const std::string &name)
{
    if (this->_windows.count(name) == 0)
        LOG.error("Can't delete window: " + name);
    else
        _windows[name]->hide();
//    delete _windows.at(name);
//    _windows.erase(name);
    return *this;
}

bool View::Graphics::doesWindowExist(const std::string &name)
{
    return this->_windows.count(name) != 0;
}

View::IGraphics &View::Graphics::closeAllWindow()
{
    std::string name;
    for (auto &it : _windows)
        it.second->hide();
//    while (!_windows.empty())
//        closeWindow(_windows.begin()->first);

    return *this;
}
