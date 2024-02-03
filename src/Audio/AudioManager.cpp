#include "AudioManager.hpp"

namespace Gravy::Audio
{
    ma_ex_context *AudioManager::context = nullptr;
    uint32_t AudioManager::sampleRate = 44100;
    uint32_t AudioManager::channels = 2;
    ma_format AudioManager::format = ma_format_f32;
    ma_device_data_proc AudioManager::dataProc = nullptr;
    std::vector<AudioSource *> AudioManager::sources;
    RingBuffer<AudioSource *> AudioManager::playbackEndedQueue;

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

            sources.clear();

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

    void AudioManager::Remove(AudioSource *source)
    {
        if (context == nullptr)
            return;

        int64_t index = -1;

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

        // AudioListener listener = AudioListener.Instance;

        // if(listener == null)
        //     return;

        // Vector3 position = listener.transform.position;
        // Vector3 forward = listener.transform.forward;
        // Vector3 velocity = listener.transform.position;

        // ma_ex_audio_listener_set_position(listener.Handle, position.X, position.Y, position.Z);
        // ma_ex_audio_listener_set_direction(listener.Handle, forward.X, forward.Y, forward.Z);
        // ma_ex_audio_listener_set_velocity(listener.Handle, velocity.X, velocity.Y, velocity.Z);

        // for(size_t i = 0; i < sources.size(); i++)
        // {
        //     if(sources[i]->GetSpatial() && sources[i]->GetIsPlaying())
        //     {
        //         position = sources[i].audioSource.transform.position;
        //         forward = sources[i].audioSource.transform.forward;
        //         velocity = sources[i].audioSource.transform.velocity;
        //         MiniAudio.ma_ex_audio_source_set_position(sources[i].audioSource.Handle, position.X, position.Y, position.Z);
        //         MiniAudio.ma_ex_audio_source_set_direction(sources[i].audioSource.Handle, forward.X, forward.Y, forward.Z);
        //         MiniAudio.ma_ex_audio_source_set_velocity(sources[i].audioSource.Handle, velocity.X, velocity.Y, velocity.Z);
        //     }
        // }
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