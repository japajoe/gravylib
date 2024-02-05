#include "AudioListener.hpp"
#include "AudioManager.hpp"

namespace Gravy::Audio
{
    AudioListener::AudioListener()
    {
        handle = nullptr;
        handle = ma_ex_audio_listener_init(AudioManager::GetContext());
        position = Vector3(0.0f, 0.0f, 0.0f);
        forward = Vector3(0.0f, 0.0f, -1.0f);
        velocity = Vector3(0.0f, 0.0f, 0.0f);

        if (handle != nullptr)
        {
            ma_ex_audio_listener_set_spatialization(handle, MA_TRUE);
            AudioManager::Add(this);
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

    void AudioListener::SetPosition(const Vector3 &position)
    {
        this->position = position;
    }

    Vector3 AudioListener::GetPosition()
    {
        return position;
    }

    void AudioListener::SetForward(const Vector3 &forward)
    {
        this->forward = forward;
    }

    Vector3 AudioListener::GetForward()
    {
        return forward;
    }

    void AudioListener::SetVelocity(const Vector3 &velocity)
    {
        this->velocity = velocity;
    }

    Vector3 AudioListener::GetVelocity()
    {
        return velocity;
    }

    ma_ex_audio_listener *AudioListener::GetHandle() const
    {
        return handle;
    }
};