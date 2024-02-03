#include "AudioSource.hpp"
#include "AudioManager.hpp"
#include <functional>
#include <iostream>
#include <iomanip>
#include <cstring>

namespace Gravy::Audio
{
    AudioSource::AudioSource()
    {
        this->volume = 1.0f;
        this->pitch = 1.0f;
        this->isLooping = false;
        this->spatial = false;
        this->minDistance = 1.0f;
        this->maxDistance = 100.0f;
        this->dopplerFactor = 1.0f;
        attenuationModel = AttenuationModel::Linear;

        ma_ex_audio_source_callbacks callbacks = {0};
        callbacks.dspProc = &OnDSPCallback;
        callbacks.soundEndedProc = &OnSoundEndedCallback;
        callbacks.soundLoadedProc = &OnSoundLoadedCallback;
        callbacks.waveformProc = &OnCustomWaveformCallback;

        ma_ex_audio_source_config config = ma_ex_audio_source_config_init(AudioManager::GetContext(), callbacks);

        handle = ma_ex_audio_source_init(&config);

        if (handle != nullptr)
        {
            ma_ex_audio_source_set_callbacks_user_data(handle, this);

            // ma_ex_dsp_node_config dspNodeConfig = ma_ex_dsp_node_config_init(2, AudioManager::GetSampleRate(), &OnDSPNodeCallback, this);
            // ma_engine *engine = AudioManager::GetContext()->engine;
            // memset(&dspNode, 0, sizeof(ma_ex_dsp_node));
            // ma_ex_dsp_node_init(ma_engine_get_node_graph(engine), &dspNodeConfig, nullptr, &dspNode);
            // ma_node_attach_output_bus(&dspNode, 0, ma_engine_get_endpoint(engine), 0);

            AudioManager::Add(this);
        }
    }

    void AudioSource::Dispose()
    {
        Stop();
        ma_ex_audio_source_uninit(handle);
    }

    void AudioSource::Stop()
    {
        ma_ex_audio_source_stop(handle);
        ma_ex_audio_source_set_pcm_position(handle, 0);
    }

    void AudioSource::Play()
    {
        Stop();
        ma_ex_audio_source_play_from_waveform_proc(handle);
    }

    void AudioSource::Play(AudioClip *clip)
    {
        Stop();
        if (clip->GetDataSize() == 0)
        {
            ma_ex_audio_source_play(handle, clip->GetPilePath().c_str(), clip->GetStreamFromDisk() ? MA_TRUE : MA_FALSE);
        }
        else
        {
            ma_ex_audio_source_play_from_memory(handle, clip->GetData(), clip->GetDataSize());
        }
    }

    void AudioSource::Seek(ma_uint64 frameIndex)
    {
        ma_ex_audio_source_set_pcm_position(handle, frameIndex);
    }

    void AudioSource::SetVolume(float volume)
    {
        this->volume = volume;
        ApplyVolume();
    }

    float AudioSource::GetVolume() const
    {
        return volume;
    }

    void AudioSource::SetPitch(float pitch)
    {
        this->pitch = pitch;
        ApplyPitch();
    }

    float AudioSource::GetPitch() const
    {
        return pitch;
    }

    void AudioSource::SetIsLooping(bool isLooping)
    {
        this->isLooping = isLooping;
        ApplyIsLooping();
    }

    bool AudioSource::GetIsLooping() const
    {
        return isLooping;
    }

    bool AudioSource::IsPlaying() const
    {
        return ma_ex_audio_source_get_is_playing(handle) > 0;
    }

    void AudioSource::SetSpatial(bool spatial)
    {
        this->spatial = spatial;
        ApplySpatial();
    }

    bool AudioSource::GetSpatial() const
    {
        return spatial;
    }

    void AudioSource::SetMinDistance(float minDistance)
    {
        this->minDistance = minDistance;
        ApplyMinDistance();
    }

    float AudioSource::GetMinDistance() const
    {
        return minDistance;
    }

    void AudioSource::SetMaxDistance(float maxDistance)
    {
        this->maxDistance = maxDistance;
        ApplyMaxDistance();
    }

    float AudioSource::GetMaxDistance() const
    {
        return maxDistance;
    }

    void AudioSource::SetDopplerFactor(float dopplerFactor)
    {
        this->dopplerFactor = dopplerFactor;
        ApplyDopplerFactor();
    }

    float AudioSource::GetDopplerFactor() const
    {
        return dopplerFactor;
    }

    ma_uint64 AudioSource::GetPosition() const
    {
        ma_uint64 position = 0;
        ma_ex_audio_source_get_pcm_position(handle, &position);
        return position;
    }

    double AudioSource::GetPositionInSeconds() const
    {
        ma_uint64 position = 0;
        ma_ex_audio_source_get_pcm_position(handle, &position);
        if (position == 0)
            return 0;
        return static_cast<double>(position) / static_cast<double>(AudioManager::GetSampleRate());
    }

    ma_uint64 AudioSource::GetLength() const
    {
        ma_uint64 length = 0;
        ma_ex_audio_source_get_pcm_length(handle, &length);
        return length;
    }

    double AudioSource::GetLengthInSeconds() const
    {
        ma_uint64 length = 0;
        ma_ex_audio_source_get_pcm_length(handle, &length);
        if (length == 0)
            return 0;
        return static_cast<double>(length) / static_cast<double>(AudioManager::GetSampleRate());
    }

    std::string AudioSource::GetFormattedTimeStamp(double seconds)
    {
        int hours = static_cast<int>(seconds / 3600);
        int minutes = static_cast<int>((seconds - hours * 3600) / 60);
        int remainingSeconds = static_cast<int>(seconds - hours * 3600 - minutes * 60);

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << remainingSeconds;

        return oss.str();
    }

    void AudioSource::OnDSPCallback(void *pEngineNode, void *pFramesOut, const void *pFramesIn, ma_uint64 frameCount, ma_int32 channels, void *pUserData)
    {
        if (pUserData)
        {
            AudioSource *source = reinterpret_cast<AudioSource *>(pUserData);
            if (source->dsp)
            {
                source->dsp(pEngineNode, pFramesOut, pFramesIn, frameCount, channels);
            }
        }
    }

    // This is called from the audio thread so receivers should move the message to the main thread
    void AudioSource::OnSoundEndedCallback(void *pUserData, ma_sound *pSound)
    {
        if (pUserData)
        {
            AudioSource *source = reinterpret_cast<AudioSource *>(pUserData);
            AudioManager::SetPlaybackEndedForSource(source);
        }
    }

    void AudioSource::OnSoundLoadedCallback(ma_sound *pSound, void *pUserData)
    {
        if (pUserData)
        {
            AudioSource *source = reinterpret_cast<AudioSource *>(pUserData);

            // ma_node_attach_output_bus(pSound, 0, &source->dspNode, 0);

            source->ApplyAllProperties();

            if (source->soundLoaded)
            {
                source->soundLoaded(pSound);
            }
        }
    }

    void AudioSource::OnCustomWaveformCallback(void *pWaveform, void *pFramesOut, ma_uint64 frameCount, ma_uint32 channels, void *pUserData)
    {
        if (pUserData)
        {
            AudioSource *source = reinterpret_cast<AudioSource *>(pUserData);
            if (source->customWaveform)
            {
                source->customWaveform(pWaveform, pFramesOut, frameCount, channels);
            }
        }
    }

    void AudioSource::OnDSPNodeCallback(const float **ppFramesIn, ma_uint32 *pFrameCountIn, float **ppFramesOut, ma_uint32 *pFrameCountOut, void *pUserData)
    {
        if (pUserData)
        {
            printf("OnDSPNodeCallback %d\n", *pFrameCountIn);
        }
    }

    // Called by audio manager from the main thread
    void AudioSource::TriggerPlaybackEndedCallback()
    {
        if (soundEnded)
        {
            soundEnded();
        }
    }

    void AudioSource::ApplyAllProperties()
    {
        ApplyIsLooping();
        ApplyVolume();
        ApplyPitch();
        ApplySpatial();
        ApplyMinDistance();
        ApplyMaxDistance();
        ApplyDopplerFactor();
        ApplyAttenuationModel();
    }

    void AudioSource::ApplyIsLooping()
    {
        ma_ex_audio_source_set_loop(handle, isLooping ? MA_TRUE : MA_FALSE);
    }

    void AudioSource::ApplyVolume()
    {
        ma_ex_audio_source_set_volume(handle, volume);
    }

    void AudioSource::ApplyPitch()
    {
        ma_ex_audio_source_set_pitch(handle, pitch);
    }

    void AudioSource::ApplySpatial()
    {
        ma_ex_audio_source_set_spatialization(handle, spatial ? MA_TRUE : MA_FALSE);
    }

    void AudioSource::ApplyMinDistance()
    {
        ma_ex_audio_source_set_min_distance(handle, minDistance);
    }

    void AudioSource::ApplyMaxDistance()
    {
        ma_ex_audio_source_set_max_distance(handle, maxDistance);
    }

    void AudioSource::ApplyDopplerFactor()
    {
        ma_ex_audio_source_set_doppler_factor(handle, dopplerFactor);
    }

    void AudioSource::ApplyAttenuationModel()
    {
        ma_attenuation_model model = static_cast<ma_attenuation_model>(attenuationModel);
        ma_ex_audio_source_set_attenuation_model(handle, model);
    }
};