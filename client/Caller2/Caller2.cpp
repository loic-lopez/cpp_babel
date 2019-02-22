// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// caller1.cpp created 08/10/17

#include "ClientCore.hpp"
#include "HostUDP.hpp"
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    Controller::IClient *client = new Controller::ClientCore();
    client->initSound(2, 120, 48000);

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    auto Udp_Send = new Network::SenderUDP(argv[1], std::atoi(argv[2]));

    Udp_Send->Connect();

    client->getStreamer().onSampleGet([&] (Sound::RawSound sound) {
        Protocol::SoundPacket soundPacket;

        auto enc = client->getCodec().encode(sound);
        soundPacket.magiccode = Protocol::MAGIC_CODE_SOUND_PACKET;
        soundPacket.timestamp = std::time(0);
        soundPacket.size = enc.second;
        Udp_Send->Send(soundPacket, enc.first);
    });

    client->getStreamer().startStream();
    return (0);
}