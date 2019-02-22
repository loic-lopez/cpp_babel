#pragma once

#include "ISoundStream.hpp"
#include "OpusCodec.hpp"
#include "PortAudioStream.hpp"
#include "ISoundCodec.hpp"
#include "IGraphics.hpp"
#include "INetworkClient.hpp"
#include <regex>

namespace Controller
{
    class IClient
    {
      public:
        virtual ~IClient() = default;;

        virtual IClient &getGraphicEvent() = 0;
        virtual View::ActionData getServerEvent() = 0;
        virtual IClient &initGraphic() = 0;
        virtual IClient &initNetwork(const std::string &ip, int port) = 0;
        virtual IClient &initSound(int channels, int bufSize, int sampleRate) = 0;
        virtual Sound::ISoundStream &getStreamer() = 0;
        virtual Sound::ISoundCodec &getCodec() = 0;
        virtual View::IGraphics &getGraphics() = 0;
        virtual Network::INetworkClient &getNetwork() = 0;
        virtual IClient &hostAndListenUDP(int port) = 0;
        virtual IClient &connectAndSendUDP(std::string ip, int port) = 0;
        virtual IClient &loadPlugin() = 0;
        virtual IClient &loopPlugin() = 0;
        virtual IClient &refreshPlugin() = 0;
        virtual IClient &processGraphicEvent() = 0;
        virtual IClient &processServerEvent(Protocol::ProtocolData) = 0;
        virtual IClient &run() =0;
        virtual IClient &stop() =0;
    };
}
