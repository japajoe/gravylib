#ifndef GRAVY_MEMORYSTREAM_HPP
#define GRAVY_MEMORYSTREAM_HPP

#include "Stream.hpp"

namespace Gravy::System::IO
{
    class MemoryStream : public Stream
    {
    private:
        void *data;
        bool ownsMemory;
    public:
        MemoryStream(void *data, size_t size, bool copyMemory = false);
        ~MemoryStream() override;
        size_t Read(void *buffer, size_t numBytes) override;
        size_t Write(const void *buffer, size_t numBytes) override;
        ssize_t Seek(ssize_t offset, SeekOrigin origin) override;
        void Close() override;
    };
};

#endif