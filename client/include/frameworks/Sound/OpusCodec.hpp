// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// Opus.hpp created 03/10/2017

#pragma once

#include "ISoundCodec.hpp"
#include "opus.h"
#include "Logger.hpp"

namespace Sound
{
    class OpusCodec : public ISoundCodec
    {
      private:
        int _channels;
        int _bufferSize;
        int _sampleRate;
        int _durationSeconds;
        bool _stop;

        OpusEncoder *_encoder;
        OpusDecoder *_decoder;
        int _err;
        opus_int32 _enc_bytes;

      public:
        OpusCodec(int channels, int bufferSize, int sampleRate);
        ~OpusCodec() override;
        std::pair<EncodedSound, int> encode(RawSound sound) override;
        RawSound decode(EncodedSound sound, int) override;
    };
}
