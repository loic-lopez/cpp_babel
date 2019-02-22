// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// PortAudio.cpp created 03/10/2017

#include "PortAudioStream.hpp"

Sound::PortAudioStream::PortAudioStream(int channels, int bufferSize, int sampleRate)
{
    LOG.log("[PORTAUDIO] Creating");
    _channels = channels;
    _bufferSize = bufferSize;
    _sampleRate = sampleRate;

    _stop = false;
    _onSampleGetFunc = [](RawSound) {
        LOG.fatal("[PORTAUDIO] You need to set a callback first -> onSampleGet");
    };

    if ((_err = Pa_Initialize()) != paNoError)
        LOG.error(std::string("[PORTAUDIO] Pa_Init failed: ") + std::string(Pa_GetErrorText(_err)));

    if ((_err = Pa_OpenDefaultStream(&_stream,
                                     _channels, _channels, paInt16, _sampleRate,
                                     _bufferSize, nullptr, nullptr)) != paNoError) {
        LOG.error(std::string("[PORTAUDIO] Pa_OpenDefaultStream failed: ") + std::string(Pa_GetErrorText(_err)));
    }

    if ((_err = Pa_StartStream(_stream)) != paNoError)
        LOG.error(std::string("[PORTAUDIO] Start stream failed: ") + std::string(Pa_GetErrorText(_err)));

    LOG.log("[PORTAUDIO] stream open");
}

Sound::ISoundStream &Sound::PortAudioStream::startStream()
{
    LOG.log("[PORTAUDIO] Starting to record");

    RawSound _captured;

    _captured.resize(_bufferSize * _channels);

    while (!_stop) {
        _err = Pa_ReadStream(_stream, _captured.data(), _bufferSize);
        _onSampleGetFunc(_captured);
//        Pa_WriteStream(_stream, _captured.data(), _bufferSize);
    }

    LOG.log("[PORTAUDIO] Finish to record");
    return *this;
}

Sound::ISoundStream &Sound::PortAudioStream::onSampleGet(std::function<void(Sound::RawSound)> function)
{
    _onSampleGetFunc = function;
    return *this;
}

Sound::ISoundStream &Sound::PortAudioStream::stopStream()
{
    _stop = true;
    // stop stream
    if ((_err = Pa_StopStream(_stream)) != paNoError)
        std::cout << "Pa_StopStream failed: " << Pa_GetErrorText(_err) << "\n";

// cleanup portaudio
    if ((_err = Pa_CloseStream(_stream)) != paNoError)
        std::cout << "Pa_CloseStream failed: " << Pa_GetErrorText(_err) << "\n";

    if ((_err = Pa_Terminate()) != paNoError)
        std::cout << "Pa_Terminate failed: " << Pa_GetErrorText(_err) << "\n";
    return *this;
}

Sound::ISoundStream &Sound::PortAudioStream::startOutput(Sound::RawSound sound)
{
    Pa_WriteStream(_stream, sound.data(), _bufferSize);
    return *this;
}

Sound::PortAudioStream::~PortAudioStream()
{
//    stopStream();
}