#ifndef GRAVY_THREAD_HPP
#define GRAVY_THREAD_HPP

#include <cstdint>

namespace Gravy::System::Threading
{
    class Thread
    {
    public:
        static void Sleep(uint32_t milliseconds);
        static uint64_t GetCurrentThreadId();
    };
};

#endif