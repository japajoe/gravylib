#include "AudioManager.hpp"

namespace Gravy::Audio
{
    ma_ex_context *AudioManager::context = nullptr;
    uint32_t AudioManager::sampleRate = 44100;
    uint32_t AudioManager::channels = 2;
    ma_format AudioManager::format = ma_format_f32;
    ma_device_data_proc AudioManager::dataProc = nullptr;
    std::vector<AudioSource *> AudioManager::sources;
    std::vector<AudioListener*> AudioManager::listeners;
    ConcurrentQueue<AudioSource *> AudioManager::playbackEndedQueue;

    void AudioManager::Initialize()
    {
        dataProc = &OnDataProcess;

        ma_ex_context_config config = {0};
        config.sampleRate = sampleRate;
        config.channels = channels;
        config.format = format;
        config.dataProc = dataProc;

        context = ma_ex_context_init(&config);
    }

    void AudioManager::Deinitialize()
    {
        if (context != nullptr)
        {
            for (size_t i = 0; i < sources.size(); i++)
            {
                sources[i]->Dispose();
            }

            for (size_t i = 0; i < listeners.size(); i++)
            {
                listeners[i]->Dispose();
            }

            sources.clear();
            listeners.clear();

            ma_ex_context_uninit(context);
            context = nullptr;
        }
    }

    void AudioManager::Add(AudioSource *source)
    {
        if (context == nullptr)
            return;

        for (size_t i = 0; i < sources.size(); i++)
        {
            if (sources[i] == source)
                return;
        }

        sources.push_back(source);
    }

    void AudioManager::Add(AudioListener *listener)
    {
        if (context == nullptr)
            return;

        for (size_t i = 0; i < listeners.size(); i++)
        {
            if (listeners[i] == listener)
                return;
        }

        listeners.push_back(listener);
    }

    void AudioManager::Remove(AudioSource *source)
    {
        if (context == nullptr)
            return;

        ssize_t index = -1;

        for (size_t i = 0; i < sources.size(); i++)
        {
            if (sources[i] == source)
            {
                index = i;
                break;
            }
        }

        if (index >= 0)
        {
            sources[index]->Dispose();
            sources.erase(sources.begin() + index);
        }
    }

    void AudioManager::Remove(AudioListener *listener)
    {
        if (context == nullptr)
            return;

        ssize_t index = -1;

        for (size_t i = 0; i < listeners.size(); i++)
        {
            if (listeners[i] == listener)
            {
                index = i;
                break;
            }
        }

        if (index >= 0)
        {
            listeners[index]->Dispose();
            listeners.erase(listeners.begin() + index);
        }
    }

    void AudioManager::Update()
    {
        if (playbackEndedQueue.GetCount() > 0)
        {
            AudioSource *source = nullptr;
            while (playbackEndedQueue.TryDequeue(source))
            {
                source->TriggerPlaybackEndedCallback();
            }
        }

        if(listeners.size() == 0)
            return;

        for(size_t i = 0; i < listeners.size(); i++)
        {
            auto listener = listeners[i];
            
            if(!listener)
                continue;
            
            auto handle = listener->GetHandle();
            
            if(!handle)
                continue;

            Vector3 position = listener->GetPosition();
            Vector3 forward = listener->GetForward();
            Vector3 velocity = listener->GetVelocity();

            ma_ex_audio_listener_set_position(handle, position.x, position.y, position.z);
            ma_ex_audio_listener_set_direction(handle, forward.x, forward.y, forward.z);
            ma_ex_audio_listener_set_velocity(handle, velocity.x, velocity.y, velocity.z);

            for(size_t j = 0; j < sources.size(); j++)
            {
                if(sources[j]->GetSpatial() && sources[j]->IsPlaying())
                {
                    auto source = sources[j];

                    if(!source)
                        continue;
                    
                    auto handle = source->GetHandle();

                    if(!handle)
                        continue;

                    position = source->GetPosition();
                    forward = source->GetForward();
                    velocity = source->GetVelocity();

                    ma_ex_audio_source_set_position(handle, position.x, position.y, position.z);
                    ma_ex_audio_source_set_direction(handle, forward.x, forward.y, forward.z);
                    ma_ex_audio_source_set_velocity(handle, velocity.x, velocity.y, velocity.z);
                }
            }
        }
    }

    void AudioManager::SetPlaybackEndedForSource(AudioSource *source)
    {
        playbackEndedQueue.Enqueue(source);
    }

    void AudioManager::OnDataProcess(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
    {
        ma_engine_read_pcm_frames((ma_engine *)pDevice->pUserData, pOutput, frameCount, nullptr);
    }

    ma_ex_context *AudioManager::GetContext()
    {
        return context;
    }

    uint32_t AudioManager::GetSampleRate()
    {
        return AudioManager::sampleRate;
    }
};