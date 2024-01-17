#include "System/Net/NetworkStream.hpp"

namespace Gravy::System::Net
{
    NetworkStream::NetworkStream()
    {
        this->socket = nullptr;
    }

    NetworkStream::NetworkStream(Socket *socket)
    {
        this->socket = socket;
    }

    NetworkStream::~NetworkStream()
    {

    }

    ssize_t NetworkStream::Read(void *buffer, size_t size)
    {
        if(socket)
            return socket->Read(buffer, size);
        return 0;
    }

    ssize_t NetworkStream::Write(const void *buffer, size_t size)
    {
        if(socket)
            return socket->Write(buffer, size);
        return 0;
    }

    void NetworkStream::Close()
    {

    }
};