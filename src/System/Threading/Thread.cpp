#include "Thread.hpp"
#include <thread>

namespace Gravy::System::Threading
{
    void Thread::Sleep(uint32_t milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    uint64_t Thread::GetCurrentThreadId()
    {
        return std::hash<std::thread::id>{}(std::this_thread::get_id());
    }    
};