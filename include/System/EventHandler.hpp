#ifndef GRAVY_EVENTHANDLER_HPP
#define GRAVY_EVENTHANDLER_HPP

#include <vector>
#include <functional>

namespace Gravy::System
{
    template<typename T>
    class EventHandler
    {
    private:
        std::vector<T> callbacks;
    public:

        template<typename ... Param>
        void operator () (Param ... param)
        {
            for (const auto& callback : callbacks)
            {
                if (callback)
                {
                    callback(param...);
                }
            }
        }

        void operator += (const T &callback)
        {
            callbacks.push_back(callback);
        }
    };
};

#endif