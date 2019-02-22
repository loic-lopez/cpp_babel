// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// ISoundCodec.hpp created 03/10/2017

#pragma once

#include <vector>

namespace Sound
{
    using EncodedSound = std::vector<unsigned char>;
    using RawSound = std::vector<unsigned short>;

    class ISoundCodec
    {
      public:
        virtual ~ISoundCodec()
        {}

        virtual std::pair<EncodedSound, int> encode(RawSound) = 0;
        virtual RawSound decode(EncodedSound, int) = 0;
    };
}
