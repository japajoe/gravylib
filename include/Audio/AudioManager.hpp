#ifndef GRAVY_AUDIOMANAGER_HPP
#define GRAVY_AUDIOMANAGER_HPP

#include "../External/miniaudioex/miniaudioex.h"
#include "../System/Collections/RingBuffer.hpp"
#include "AudioSource.hpp"
#include <vector>
#include <cstdint>

using namespace Gravy::System::Collections;

namespace Gravy::Audio
{
    class AudioManager 
    {
    private:
        static ma_ex_context *context;
        static uint32_t sampleRate;
        static uint32_t channels;
        static ma_format format;
        static ma_device_data_proc dataProc;
        static std::vector<AudioSource*> sources;
        static RingBuffer<AudioSource*> playbackEndedQueue;
        static void OnDataProcess(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount);
    public:
        static void Initialize();
        static void Deinitialize();
        static void Add(AudioSource *source);
        static void Remove(AudioSource *source);
        static void Update();
        static void SetPlaybackEndedForSource(AudioSource *source);
        static ma_ex_context *GetContext();
        static uint32_t GetSampleRate();
    };
};
#endif