#include "System/IO/Stream.hpp"

namespace Gravy::System::IO
{
    Stream::Stream()
    {
        size = 0;
        readPosition = 0;
        writePosition = 0;
    }

    Stream::~Stream() 
    {

    }

    size_t Stream::Read(void *buffer, size_t size)
    {
        return 0;
    }

    size_t Stream::Write(const void *buffer, size_t size)
    {
        return 0;
    }

    ssize_t Stream::Seek(ssize_t offset, SeekOrigin origin)
    {
        return 0;
    }

    size_t Stream::GetReadPosition() const
    {
        return readPosition;
    }

    size_t Stream::GetWritePosition() const
    {
        return writePosition;
    }

    size_t Stream::GetSize() const
    {
        return size;
    }

    void Stream::Close()
    {

    }
};