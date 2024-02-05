#ifndef GRAVY_AUDIOLISTENER_HPP
#define GRAVY_AUDIOLISTENER_HPP

#include <string>
#include "../External/miniaudioex/miniaudioex.h"
#include "../System/Numerics/Vector3.hpp"

namespace Gravy::Audio
{
    using namespace Gravy::System::Numerics;

    class AudioListener 
    {
    private:
        ma_ex_audio_listener *handle;
        Vector3 position;
        Vector3 forward;
        Vector3 velocity;
    public:
        AudioListener();
        void Dispose();
        void SetPosition(const Vector3 &position);
        Vector3 GetPosition();
        void SetForward(const Vector3 &forward);
        Vector3 GetForward();
        void SetVelocity(const Vector3 &velocity);
        Vector3 GetVelocity();
        ma_ex_audio_listener *GetHandle() const;
    };
};

#endif