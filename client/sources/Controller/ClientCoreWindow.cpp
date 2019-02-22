// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// ClientCoreWindow.cpp created 07/10/17

#include "ClientCore.hpp"

Controller::IClient &Controller::ClientCore::callByFriendWindow(const std::string &contact_name)
{
    View::IWindow &window = _graphics->createWindow("Babel Skype - CallByFriend").loadCSS("../css/register_dark.css").setMinSize(500, 300).setSize(1280, 720);

    std::pair<int, int> windowSize = window.getSize();
    std::string calling(" is calling you");

    window.createZone("contact_called_name", View::TEXT).setText(contact_name + calling).setSize((contact_name.size() + calling.size()) * 30, 35).place(50 - (((contact_name.size() + calling.size()) * 70) / 100), 10).setTextSize(25);
    window.createZone("call_picture", View::TEXT).setSize(256, 256).place(50 - ((256 * 100 / 1280) / 2), (256 * 100 / 720) - 10);
    window.createZone("accept_call", View::BUTTON).setSize(128, 128).place(49 - (128 * 100 / 1280), 70);
    window.createZone("deny_call", View::BUTTON).setSize(128, 128).place(51, 70);

    window.getZone("accept_call").onAction([&] () {
        acceptCallFrom(_caller, DEFAULT_PORT_HOST_UDP);
        HostFirst(_ip_other, DEFAULT_PORT_HOST_UDP);
        _graphics->getWindow("Babel Skype - CallByFriend").hide();
        callWindow(_caller);
    });
    window.getZone("deny_call").onAction([&] () {
        _graphics->closeWindow("Babel Skype - CallByFriend");
        denyCallFrom(_caller);
    });

    window.show();
    _graphics->switchToWindow("Babel Skype - CallByFriend");
}

Controller::IClient &Controller::ClientCore::callWindow(const std::string &contact_name)
{
    View::IWindow &window = _graphics->createWindow("Babel Skype - Call").loadCSS("../css/register_dark.css").setMinSize(500, 300).setSize(1280, 720);

    std::pair<int, int> windowSize = window.getSize();
    window.createZone("contact_called_name", View::TEXT).setText(contact_name).setSize(contact_name.size() * 30, 35).place(50 - ((contact_name.size() * 70) / 100), 10).setTextSize(25);
    window.createZone("call_picture", View::TEXT).setSize(256, 256).place(50 - ((256 * 100 / 1280) / 2), (256 * 100 / 720) - 10);
    window.createZone("mute_button", View::BUTTON).setSize(128, 128).place(49 - (128 * 100 / 1280), 70);
    window.createZone("stop_call", View::BUTTON).setSize(128, 128).place(51, 70);
    window.getZone("stop_call").onAction([&] () {
        this->stop();
    });

    window.show();
}

Controller::IClient &Controller::ClientCore::connectServerWindow()
{
    _graphics->createWindow("Babel Skype - Connect To Server").loadCSS("../css/register_dark.css").setMinSize(800, 600).setSize(1280, 720);
    std::pair<int, int> windowSize = _graphics->getWindow("Babel Skype - Connect To Server").getSize();

    _graphics->getWindow("Babel Skype - Connect To Server").createZone("connect_server_ip_title", View::TEXT).setText("I.P. address:").setSize(225, 50).place(30, 30).setTextSize(30); //400, 200
    _graphics->getWindow("Babel Skype - Connect To Server").createZone("connect_server_ip_input", View::INPUT_BOX).setSize(200, 25).place(50, 32).setText("127.0.0.1"); // 600, 200

    _graphics->getWindow("Babel Skype - Connect To Server").createZone("connect_server_port_title", View::TEXT).setText("Port:").setSize(200, 50).place(30, 40).setTextSize(28); // 400, 300
    _graphics->getWindow("Babel Skype - Connect To Server").createZone("connect_server_port_input", View::INPUT_BOX).setSize(200, 25).place(50, 42).setText("4000"); // 600, 300

    _graphics->getWindow("Babel Skype - Connect To Server").createZone("connect_server_button", View::BUTTON).setText("Connect").setSize(15 * 8, 35).place(50, 50).setTextSize(20); // 600, 400

    _graphics->getWindow("Babel Skype - Connect To Server").createZone("connect_server_exit_button", View::BUTTON).setText("Exit").setSize(15 * 8, 35).place(50, 75).onAction([&] () {
       this->stop();
    }).setTextSize(30);
    _graphics->getWindow("Babel Skype - Connect To Server").show();

    _graphics->getWindow("Babel Skype - Connect To Server").getZone("connect_server_button").onAction([&]() {
        auto ip = _graphics->getWindow("Babel Skype - Connect To Server").getZone("connect_server_ip_input").getText();
        std::string portString = _graphics->getWindow("Babel Skype - Connect To Server").getZone("connect_server_port_input").getText();
        std::regex ip_regex("(\\d{1,3}(\\.\\d{1,3}){3})");
        std::regex port_regex("^[0-9]*$");
        int port = 0;
        if (ip.empty())
        {
            ip = "127.0.0.1";
            _graphics->getWindow("Babel Skype - Connect To Server").getZone("connect_server_ip_input").setText(ip).setTextSize(28);
        }

        if (portString.empty())
            portString = "4000";
        port = std::atoi(portString.c_str());

        if (!std::regex_search(ip, ip_regex) || !std::regex_search(portString, port_regex))
        {
            this->errorWindow("Wrong IP or port");
            return nullptr;
        }

        initNetwork(ip, port);

        _network->Start_Async();
        _graphics->closeWindow("Babel Skype - Connect To Server");
        loginWindow();
    });
    return *this;
}

Controller::IClient &Controller::ClientCore::homeWindow()
{
    //Get friend list
    View::IWindow &window = _graphics->createWindow("Babel Skype - Home").loadCSS("../css/home.css").setMinSize(1280, 720).setMaxSize(1280, 720).setSize(1280, 720);

    window.createZone("disconnect_button", View::BUTTON).setText("Disconnect").setSize(120, 35).place(89, 5).setTextSize(15);
    window.createZone("exit_button", View::BUTTON).setText("Exit").setSize(120, 35).place(89, 11).setTextSize(25);
    window.createZone("message_feed", View::TEXT_BOX).setText("Empty message feed").setSize(936, 550).place(15, 5).setTextSize(15);
    window.createZone("chat_input", View::INPUT_BOX).setSize(936, 35).place(15, 85).setTextSize(15);
    window.createZone("chat_send_button", View::BUTTON).setText("Send").setSize(120, 35).place(89, 85).setTextSize(25);
    window.createZone("get_friend_button", View::BUTTON).setText("Friends").setSize(120, 35).place(89, 50).setTextSize(15).onAction([&] () {
        sendNeedFriendList();
    });

    window.createZone("add_friend_button", View::BUTTON).setText("+").setSize(50,50).place(0,0).setTextSize(40);

    window.show();

    window.getZone("exit_button").onAction([this]() {
        this->stop();
    });

    window.getZone("disconnect_button").onAction([&] () -> void {
        _network->Stop_Async();
        _graphics->closeAllWindow();
        connectServerWindow();
    });

    window.getZone("chat_send_button").onAction([&] () -> void {
        std::string registerLoginText = window.getZone("chat_input").getText();

    });

    window.getZone("add_friend_button").onAction([&]() {
        View::IWindow &w = _graphics->createWindow("Babel Skype - Add Friend").loadCSS("../css/home.css").setMinSize(400,400);
        w.createZone("field_friend_text", View::INPUT_BOX).setSize(300, 100).place(25, 0).setTextSize(20);
        w.createZone("add friend_button", View::BUTTON).setText("ADD").setTextSize(30).setSize(300, 200).place(25,50).onAction([&] () {
            this->_bro = w.getZone("field_friend_text").getText();

            _onReceiveOk = [&] () {
                successWindow();
                _graphics->deleteWindow("Babel Skype - Add Friend");
            };

            _onReceiveUserDontExist = [&] () {
                errorWindow("User " + _bro + " don't exist");
            };

            _onReceiveUserAlreadyYourFriend = [&] () {
                errorWindow("User " + _bro + " is already your friend");
            };

            sendFriendRequest(_bro);
        });

        w.createZone("add friend_close", View::BUTTON).setText("X").setTextSize(30).setSize(100, 100).place(90,0).onAction([&] () {
            _graphics->closeWindow("Babel Skype - Add Friend");
        });

        w.show();
    });

    return *this;
}

Controller::IClient &Controller::ClientCore::errorWindow(const std::string &error)
{
    View::IWindow &window = _graphics->createWindow("Babel Skype - Error").loadCSS("../css/register_dark.css").setMinSize(400, 200).setSize(500, 300);

    constexpr auto max = 500 * 12 / 10;
    auto fontSize = max / error.size();
    auto start = 500 * 13 / 10 - max;
    start = start * 100 / 500;
    window.createZone("error_message", View::TEXT).setText(error).setSize(500, 60).place(start, 35).setTextSize(fontSize);
    window.createZone("error_close_button", View::BUTTON).setText("Close").setSize(500, 65).place(0, 65).setTextSize(20);
    window.createZone("error_picture", View::TEXT).setSize(64, 64).place(50 - ((64 * 100 / 500) / 2), 5);

    window.getZone("error_close_button").onAction([&] () -> void {
        _graphics->deleteWindow("Babel Skype - Error");
    });

    window.show();
    return *this;
}

Controller::IClient &Controller::ClientCore::successWindow(const std::string &msg)
{
    View::IWindow &window = _graphics->createWindow("Babel Skype - Success").loadCSS("../css/register_dark.css").setMinSize(400, 200).setSize(500, 300);

    constexpr auto max = 500 * 12 / 10;
    auto fontSize = max / msg.size();
    auto start = 500 * 13 / 10 - max;
    start = start * 100 / 500;
    window.createZone("error_message", View::TEXT).setText(msg).setSize(500, 100).place(start, 45).setTextSize(fontSize);
    window.createZone("error_close_button", View::BUTTON).setText("Close").setSize(500, 65).place(0, 65).setTextSize(20);
    window.getZone("error_close_button").onAction([&] () -> void {
        _graphics->deleteWindow("Babel Skype - Success");
    });

    window.show();
    return *this;
}


Controller::IClient &Controller::ClientCore::registerWindow()
{
    View::IWindow &window = _graphics->createWindow("Babel Skype - Register").loadCSS("../css/register_dark.css").setMinSize(800, 600).setSize(1280, 720);

    window.createZone("register_login", View::TEXT).setText("Login:").setSize(110, 50).place(19, 30).setTextSize(30);
    window.createZone("register_login_input", View::INPUT_BOX).setSize(200, 25).place(50, 32);

    window.createZone("register_password", View::TEXT).setText("Password:").setSize(200, 50).place(19, 40).setTextSize(28);
    window.createZone("register_password_input", View::INPUT_BOX).setSize(200, 25).place(50, 42);

    window.createZone("register_password_confirm", View::TEXT).setText("Confirm your password:").setSize(400, 50).place(19, 50).setTextSize(28);
    window.createZone("register_password_confirm_input", View::INPUT_BOX).setSize(200, 25).place(50, 52);

    window.createZone("register_button", View::BUTTON).setText("Register").setSize(15 * 8, 35).place(45, 65).setTextSize(20);
    window.createZone("exit_button", View::BUTTON).setText("Exit").setSize(15 * 8, 35).place(45, 75).setTextSize(20);

    window.show();

    window.getZone("exit_button").onAction([this]() {
        QApplication::quit();
    });
    window.getZone("register_button").onAction([&] () -> void {
        std::string registerLoginText = window.getZone("register_login_input").getText();
        std::string registerPasswordText = window.getZone("register_password_input").getText();
        std::string registerPasswordConfirmationText = window.getZone("register_password_confirm_input").getText();

        this->_bro = registerLoginText;
        loginProcess(registerLoginText, registerPasswordText);

        if (!registerPasswordText.empty() && !registerPasswordConfirmationText.empty()
            && registerPasswordText == registerPasswordConfirmationText && !registerLoginText.empty())
        {
            _onReceiveOk = [&] () {
                _graphics->closeWindow("Babel Skype - Register");
                homeWindow();
            };

            _onReceiveBadLoginFormat = [&] () {
              errorWindow("Bad login or password format");
            };

            _onReceiveUserAlreadyExist = [&] () {
                errorWindow("Username already taken, why not use: Xx" + this->_bro + "xX");
            };
            sendRegisterCMD(registerLoginText, registerPasswordText);
        }
        else
        {
                if (registerLoginText.empty())
                    this->errorWindow("Login field cannot be empty.");
                else if (registerPasswordText.empty() && registerPasswordConfirmationText.empty())
                    this->errorWindow("Password and password confirmation fields cannot be empty.");
                else if (registerPasswordText.empty())
                    this->errorWindow("Password field cannot be empty.");
                else if (registerPasswordConfirmationText.empty())
                    this->errorWindow("Password confirmation field cannot be empty.");
                else if (registerPasswordText != registerPasswordConfirmationText)
                    this->errorWindow("Password and password confirmation are not equals.");
        }
    });
    return *this;
}

Controller::IClient *Controller::ClientCore::loginWindow()
{
    _graphics->createWindow("Babel Skype - Login").loadCSS("../css/register_dark.css").setMinSize(800, 600).setSize(1280, 720);
    std::pair<int, int> windowSize = _graphics->getWindow("Babel Skype - Login").getSize();

    _graphics->getWindow("Babel Skype - Login").createZone("login_title_login", View::TEXT).setText("Login:").setSize(110, 50).place(36, 30).setTextSize(30); //400, 200
    _graphics->getWindow("Babel Skype - Login").createZone("login_input_login", View::INPUT_BOX).setSize(200, 25).place(50, 32); // 600, 200

    _graphics->getWindow("Babel Skype - Login").createZone("login_title_password", View::TEXT).setText("Password:").setSize(200, 50).place(36, 40).setTextSize(28); // 400, 300
    _graphics->getWindow("Babel Skype - Login").createZone("login_input_password", View::INPUT_BOX).setSize(200, 25).place(50, 42); // 600, 300

    _graphics->getWindow("Babel Skype - Login").createZone("login_button", View::BUTTON).setText("Connect").setSize(15 * 8, 35).place(50, 50).setTextSize(20); // 600, 400
    _graphics->getWindow("Babel Skype - Login").createZone("register", View::TEXT).setText("No account?").setSize(200, 25).place(36, 58).setTextSize(20); // 400, 475
    _graphics->getWindow("Babel Skype - Login").createZone("register_button", View::BUTTON).setText("Register").setSize(15 * 8, 35).place(50, 57).setTextSize(20); // 600, 475
    _graphics->getWindow("Babel Skype - Login").createZone("exit_button", View::BUTTON).setText("Exit").setSize(15 * 8, 35).place(50, 71).setTextSize(20); // 600, 475

    _graphics->getWindow("Babel Skype - Login").show();

    _graphics->getWindow("Babel Skype - Login").getZone("login_button").onAction([this]() {

        auto login = _graphics->getWindow("Babel Skype - Login").getZone("login_input_login").getText();
        auto password = _graphics->getWindow("Babel Skype - Login").getZone("login_input_password").getText();
        loginProcess(login, password);
        if (login.empty() || password.empty())
        {
            errorWindow("Login or Password empty");
            return (nullptr);
        }
        _onReceiveIncorrectLogin = [&] () {
            errorWindow("Incorrect Login or Password");
        };

        _onReceiveUserDontExist = [&] () {
            errorWindow("User don't exist");
        };

        _onReceiveOk = [&] () {
            _graphics->closeAllWindow();
            this->homeWindow();
        };
        sendLoginCMD(login, password);
    });

    _graphics->getWindow("Babel Skype - Login").getZone("register_button").onAction([this]() {
        _graphics->closeWindow("Babel Skype - Login");
        this->registerWindow();
    });

    _graphics->getWindow("Babel Skype - Login").getZone("exit_button").onAction([&]() {
        stop();
    });

    return this;
}
