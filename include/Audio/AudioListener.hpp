#ifndef GRAVY_AUDIOLISTENER_HPP
#define GRAVY_AUDIOLISTENER_HPP

#include <string>
#include "../External/miniaudioex/miniaudioex.h"

namespace Gravy::Audio
{
    class AudioListener 
    {
    private:
        ma_ex_audio_listener *handle;
    public:
        AudioListener();
        void Dispose();
    };
};

#endif