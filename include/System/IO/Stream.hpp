#ifndef GRAVY_STREAM_HPP
#define GRAVY_STREAM_HPP

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <string>

namespace Gravy::System::IO
{
    enum class SeekOrigin
    {
        Begin,
        Current,
        End
    };

    class Stream
    {
    protected:
        size_t size;
        size_t readPosition;
        size_t writePosition;
    public:
        Stream();
        virtual ~Stream();
        virtual size_t Read(void *buffer, size_t size);
        virtual size_t Write(const void *buffer, size_t size);
        virtual ssize_t Seek(ssize_t offset, SeekOrigin origin);
        size_t GetReadPosition() const;
        size_t GetWritePosition() const;
        size_t GetSize() const;
        virtual void Close();
    };
};

#endif