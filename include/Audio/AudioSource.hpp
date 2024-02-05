#ifndef GRAVY_AUDIOSOURCE_HPP
#define GRAVY_AUDIOSOURCE_HPP

#include <functional>
#include <string>
#include "../External/miniaudioex/miniaudioex.h"
#include "../System/Numerics/Vector3.hpp"
#include "AudioClip.hpp"

namespace Gravy::Audio
{
    using Vector3 = Gravy::System::Numerics::Vector3;
    
    enum class AttenuationModel
    {
        None,          /* No distance attenuation and no spatialization. */
        Inverse,       /* Equivalent to OpenAL's AL_INVERSE_DISTANCE_CLAMPED. */
        Linear,        /* Linear attenuation. Equivalent to OpenAL's AL_LINEAR_DISTANCE_CLAMPED. */
        Exponential    /* Exponential attenuation. Equivalent to OpenAL's AL_EXPONENT_DISTANCE_CLAMPED. */        
    };

    class AudioSource 
    {
    friend class AudioManager;
    private:
        ma_ex_audio_source *handle;
        ma_ex_dsp_node dspNode;
        float volume;
        float pitch;
        bool isLooping;
        bool spatial;
        float minDistance;
        float maxDistance;
        float dopplerFactor;
        AttenuationModel attenuationModel;
        Vector3 position;
        Vector3 forward;
        Vector3 velocity;
        void ApplyAllProperties();
        void ApplyIsLooping();
        void ApplyVolume();
        void ApplyPitch();
        void ApplySpatial();
        void ApplyMinDistance();
        void ApplyMaxDistance();
        void ApplyDopplerFactor();
        void ApplyAttenuationModel();
        static void OnDSPCallback(void *pEngineNode, void *pFramesOut, const void *pFramesIn, ma_uint64 frameCount, ma_int32 channels, void *pUserData);
        static void OnSoundEndedCallback(void *pUserData, ma_sound *pSound);
        static void OnSoundLoadedCallback(ma_sound *pSound, void *pUserData);
        static void OnCustomWaveformCallback(void *pWaveform, void *pFramesOut, ma_uint64 frameCount, ma_uint32 channels, void *pUserData);
        static void OnDSPNodeCallback(const float** ppFramesIn, ma_uint32* pFrameCountIn, float** ppFramesOut, ma_uint32* pFrameCountOut, void *pUserData);
        void TriggerPlaybackEndedCallback();
    public:
        std::function<void(void*, void*, const void*, ma_uint64, ma_int32)> dsp;
        std::function<void()> soundEnded;
        std::function<void(ma_sound*)> soundLoaded;
        std::function<void(void*, void*, ma_uint64, ma_uint32)> customWaveform;
        AudioSource();
        void Dispose();
        void Stop();
        void Play();
        void Play(AudioClip *clip);
        void Seek(ma_uint64 frameIndex);
        void SetVolume(float volume);
        float GetVolume() const;
        void SetPitch(float pitch);
        float GetPitch() const;
        void SetIsLooping(bool isLooping);
        bool GetIsLooping() const;
        bool IsPlaying() const;
        void SetSpatial(bool spatial);
        bool GetSpatial() const;
        void SetMinDistance(float minDistance);
        float GetMinDistance() const;
        void SetMaxDistance(float maxDistance);
        float GetMaxDistance() const;
        void SetDopplerFactor(float dopplerFactor);
        float GetDopplerFactor() const;
        ma_uint64 GetPositionInSamples() const;
        double GetPositionInSeconds() const;
        ma_uint64 GetLength() const;
        double GetLengthInSeconds() const;
        std::string GetFormattedTimeStamp(double seconds);
        void SetPosition(const Vector3 &position);
        Vector3 GetPosition();
        void SetForward(const Vector3 &forward);
        Vector3 GetForward();
        void SetVelocity(const Vector3 &velocity);
        Vector3 GetVelocity();
        ma_ex_audio_source *GetHandle() const;
    };
};

#endif