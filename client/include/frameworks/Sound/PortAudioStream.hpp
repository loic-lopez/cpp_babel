// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// PortAudio.hpp created 03/10/2017

#pragma once

#include <iostream>
#include <portaudio.h>
#include "Logger.hpp"
#include "ISoundStream.hpp"

namespace Sound
{
    class PortAudioStream : public ISoundStream
    {
      private:
        int _channels;
        int _bufferSize;
        int _sampleRate;
        bool _stop;

        PaError _err;
        PaStream* _stream;

        std::function<void(Sound::RawSound)> _onSampleGetFunc;

      public:
        PortAudioStream(int channels, int bufferSize, int sampleRate);
        ~PortAudioStream();
        ISoundStream &startStream() override;
        ISoundStream &onSampleGet(std::function<void(RawSound)> function) override;
        ISoundStream &stopStream() override;
        ISoundStream &startOutput(RawSound sound) override;
    };
}