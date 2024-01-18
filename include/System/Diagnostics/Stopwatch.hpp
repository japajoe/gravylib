#ifndef GRAVY_STOPWATCH_HPP
#define GRAVY_STOPWATCH_HPP

#include <chrono>

namespace Gravy::System::Diagnostics
{
    class Stopwatch 
    {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
        std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoint;
        bool running;
    public:
        Stopwatch();
        void Start();
        void Stop();
        void Reset();
        double GetElapsedMilliseconds() const;
        double GetElapsedSeconds() const;
        std::chrono::duration<double> GetElapsedTime() const;
    };
};

#endif