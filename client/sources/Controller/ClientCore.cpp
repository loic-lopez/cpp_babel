// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// ClientCore.cpp created 03/10/17

#include "ClientCore.hpp"

Controller::ClientCore::ClientCore() :
    _app(*new int, nullptr)
{
    LOG.log("Creating ClientCore");
    _graphics = nullptr;
    _network = nullptr;
//    _app = new QApplication(x);
}

Controller::ClientCore::~ClientCore()
{
}

Controller::IClient &Controller::ClientCore::stop()
{
    LOG.warning("Stopping Server Core");
    QProcess *KILL = new QProcess;
    QStringList args;
    QString program = "killall";

    args << "Sender" << "Host";
    KILL->start(program, args);

    if (_graphics)
        _graphics->stop();
    return *this;
}

Controller::IClient &Controller::ClientCore::getGraphicEvent()
{
    return *this;
}

View::ActionData Controller::ClientCore::getServerEvent()
{
    return {};
}

Controller::IClient &Controller::ClientCore::initGraphic()
{
    _graphics = new View::Graphics();
    return *this;
}

Controller::IClient &Controller::ClientCore::initNetwork(const std::string &ip, int port)
{
    _NET.start();
    _UDPRECEIVE.start();
    _UDPSEND.start();

    auto tmpNetwork = new Network::qtNetwork(ip, port);

    qRegisterMetaType<Protocol::ProtocolData>("Protocol::ProtocolData");

    connect(tmpNetwork, SIGNAL(sendDataToMain(Protocol::ProtocolData)), this, SLOT(getServerData(Protocol::ProtocolData)));
    connect(tmpNetwork, SIGNAL(serverDc()), this, SLOT(getServerDC()));
    connect(this, SIGNAL(NETSendQT(Protocol::ProtocolData)), tmpNetwork, SLOT(QT_SEND(Protocol::ProtocolData)));

    _network = tmpNetwork;
    _network->onReceived([&] (Protocol::ProtocolData data) {
       getData(data);
    });
    tmpNetwork->moveToThread(&_NET);
    return *this;
}

Controller::IClient &Controller::ClientCore::loadPlugin()
{
    return *this;
}

Controller::IClient &Controller::ClientCore::loopPlugin()
{
    return *this;
}

Controller::IClient &Controller::ClientCore::refreshPlugin()
{
    return *this;
}

Controller::IClient &Controller::ClientCore::processGraphicEvent()
{
    return *this;
}

Controller::IClient &Controller::ClientCore::run()
{
    this->connectServerWindow();
    _graphics->run();
    _app.exec();
    return *this;
}

View::IGraphics &Controller::ClientCore::getGraphics()
{
    return *_graphics;
}

Network::INetworkClient &Controller::ClientCore::getNetwork()
{
    return *_network;
}

Controller::IClient &Controller::ClientCore::initSound(int channels, int bufSize, int sampleRate)
{
    _streamer = new Sound::PortAudioStream(channels, bufSize, sampleRate);
    _codec = new Sound::OpusCodec(channels, bufSize, sampleRate);
}

Sound::ISoundStream &Controller::ClientCore::getStreamer()
{
    return *_streamer;
}

Sound::ISoundCodec &Controller::ClientCore::getCodec()
{
    return *_codec;
}

Controller::IClient &Controller::ClientCore::hostAndListenUDP(int port)
{
    auto Udp_Host = new Network::HostUDP(port);
    _udpHost = Udp_Host;

    _udpHost->onReceive([&] (Protocol::SoundPacket packet, Sound::EncodedSound enc) {
        auto dec = getCodec().decode(enc, packet.size);
        getStreamer().startOutput(dec);
    });

    Udp_Host->moveToThread(&_UDPRECEIVE);

}

Controller::IClient &Controller::ClientCore::connectAndSendUDP(std::string ip, int port)
{
    auto Udp_Send = new Network::SenderUDP(ip, port, &getStreamer());
    _udpSend = Udp_Send;

    _udpSend->Connect();

    getStreamer().onSampleGet([&] (Sound::RawSound sound) {
        Protocol::SoundPacket soundPacket;

        auto enc = getCodec().encode(sound);

        soundPacket.magiccode = Protocol::MAGIC_CODE_SOUND_PACKET;
        soundPacket.timestamp = std::time(0);
        soundPacket.size = enc.second;

        _udpSend->Send(soundPacket, enc.first);
    });


    Udp_Send->moveToThread(&_UDPSEND);
}

Protocol::ProtocolData Controller::ClientCore::makePacket(Protocol::ClientToServer cmd)
{
    Protocol::ProtocolData data;

    data.header.magiccode = Protocol::MAGIC_CODE_PACKET_HEADER;
    data.header.timestamp = std::time(0);
    data.header.cmd = cmd;
    return (data);
}

void Controller::ClientCore::getServerData(Protocol::ProtocolData data)
{
        processServerEvent(data);
}

void Controller::ClientCore::getServerDC()
{
    _network->Stop_Async();
    _graphics->closeAllWindow();
    errorWindow("Server Disconnected");
    _graphics->getWindow("Babel Skype - Error").getZone("error_close_button").onAction([&] () -> void {
        _graphics->deleteWindow("Babel Skype - Error");
        connectServerWindow();
    });
}

void Controller::ClientCore::HostFirst(std::string ip, int port)
{
    _HOST = new QProcess(this);
    QStringList args;
    QString program = QCoreApplication::applicationDirPath();
#ifdef _WIN32
    program.append("/Host.exe");
#else
    program.append("/Host");
#endif

    args << std::to_string(DEFAULT_PORT_HOST_UDP).c_str();
    _HOST->start(program, args);


    _SENDER = new QProcess(this);
    QStringList argsS;
    QString programS = QCoreApplication::applicationDirPath();
#ifdef _WIN32
    programS.append("/Sender.exe");
#else
    programS.append("/Sender");
#endif


    argsS << ip.c_str()<< std::to_string(DEFAULT_PORT_HOST_UDP).c_str();
    _SENDER->start(programS, argsS);
}

void Controller::ClientCore::HostSecond(std::string ip, int port)
{
    _HOST = new QProcess(this);
    QStringList args;
    QString program = QCoreApplication::applicationDirPath();
#ifdef _WIN32
    program.append("/Host.exe");
#else
    program.append("/Host");
#endif

    args << std::to_string(DEFAULT_PORT_HOST_UDP).c_str();
    _HOST->start(program, args);


    _SENDER = new QProcess(this);
    QStringList argsS;
    QString programS = QCoreApplication::applicationDirPath();
#ifdef _WIN32
    programS.append("/Sender.exe");
#else
    programS.append("/Sender");
#endif


    argsS << ip.c_str()<< std::to_string(DEFAULT_PORT_HOST_UDP).c_str();
    _SENDER->start(programS, argsS);
}
