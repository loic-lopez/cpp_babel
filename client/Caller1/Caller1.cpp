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

    auto Udp_Host = new Network::HostUDP(std::atoi(argv[1]));
    Udp_Host->onReceive([&] (Protocol::SoundPacket packet, Sound::EncodedSound enc) {
        auto dec = client->getCodec().decode(enc, packet.size);
        client->getStreamer().startOutput(dec);
    });

    Udp_Host->Host();
    return (0);
}