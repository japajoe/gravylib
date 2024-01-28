#ifndef GRAVY_RINGBUFFER_HPP
#define GRAVY_RINGBUFFER_HPP

#include <cstdlib>
#include <vector>
#include <mutex>
#include <condition_variable>

namespace Gravy::System::Collections
{
    template <typename T>
    class RingBuffer
    {
    private:
        std::vector<T> items;
        size_t head;
        size_t tail;
        size_t numItems;
        mutable std::mutex mutex;
        std::condition_variable condition;
    public:
        RingBuffer()
        {
            numItems = 0;
            head = 0;
            tail = 0;
        }

        RingBuffer(size_t capacity)
        {
            items.resize(capacity);
            numItems = 0;
            head = 0;
            tail = 0;
        }

        void Enqueue(const T &value)
        {
            std::lock_guard<std::mutex> lock(mutex);

            if(numItems >= items.size())
                return;
            
            items[tail] = value;
            numItems++;
            tail = (tail + 1) % items.size();
            condition.notify_one();
        }

        bool TryDequeue(T &value)
        {
            std::lock_guard<std::mutex> lock(mutex);

            if(numItems == 0)
                return false;

            value = items[head];
            head = (head + 1) % items.size();
            numItems--;
            return true;
        }

        size_t GetCount() const
        {
            std::lock_guard<std::mutex> lock(mutex);
            return numItems;
        }

        void Clear()
        {
            std::lock_guard<std::mutex> lock(mutex);
            numItems = 0;
            head = 0;
            tail = 0;
        }
    };
};

#endif