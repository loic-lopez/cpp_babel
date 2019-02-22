// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝
// Opus.cpp created 03/10/2017

#include "Sound/OpusCodec.hpp"

Sound::OpusCodec::OpusCodec(int channels, int bufferSize, int sampleRate)
{
    _channels = channels;
    _bufferSize = bufferSize;
    _sampleRate = sampleRate;

    LOG.log("[OPUS] Creating...");
    _encoder = opus_encoder_create(
        sampleRate, channels, OPUS_APPLICATION_AUDIO, &_err);
    if (_err != OPUS_OK)
        LOG.error("[OPUS] Creating encoder failed" + std::to_string(_err));

    _decoder = opus_decoder_create(
        sampleRate, channels, &_err);
    if (_err != OPUS_OK)
        LOG.error("[OPUS] Creating decoder failed" + std::to_string(_err));
    LOG.log("[OPUS] Creating... Done");
}

Sound::OpusCodec::~OpusCodec()
{
}

std::pair<Sound::EncodedSound, int> Sound::OpusCodec::encode(Sound::RawSound sound)
{
    EncodedSound encoded;

    encoded.resize(_bufferSize * _channels * 2);

    if ((_enc_bytes = opus_encode(_encoder, reinterpret_cast<opus_int16 const *>(sound.data()), _bufferSize, encoded.data(), encoded.size())) < 0)
        LOG.error("[OPUS] Encoding failed " + std::to_string(_enc_bytes));
    return std::make_pair(encoded, _enc_bytes);
}

Sound::RawSound Sound::OpusCodec::decode(Sound::EncodedSound sound, int bytes)
{
    opus_int32 dec_bytes;
    RawSound decoded;

    decoded.resize(_bufferSize * _channels);
    if ((dec_bytes = opus_decode(_decoder, sound.data(), bytes,
                                 reinterpret_cast<opus_int16 *>(decoded.data()), _bufferSize, 0)) < 0)
        LOG.error("[OPUS] Decoding failed " + std::to_string(dec_bytes));
    return decoded;
}
