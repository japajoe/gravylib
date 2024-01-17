#include "System/Signal.hpp"

namespace Gravy::System
{
    void Signal::Register(SignalType signalType, signal_handler_t handler)
    {
    #ifdef _WIN32
        __p_sig_fn_t h = static_cast<__p_sig_fn_t>(handler);
        signal(static_cast<int>(signalType), h);
    #else
        __sighandler_t h = static_cast<__sighandler_t>(handler);
        signal(static_cast<int>(signalType), h);
    #endif
    }
};