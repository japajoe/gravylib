#include "AudioListener.hpp"
#include "AudioManager.hpp"

namespace Gravy::Audio
{
    AudioListener::AudioListener()
    {
        handle = nullptr;
        handle = ma_ex_audio_listener_init(AudioManager::GetContext());

        if (handle != nullptr)
        {
            ma_ex_audio_listener_set_spatialization(handle, MA_TRUE);
        }
    }

    void AudioListener::Dispose()
    {
        if (handle != nullptr)
        {
            ma_ex_audio_listener_uninit(handle);
            handle = nullptr;
        }
    }
};