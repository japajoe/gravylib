#ifndef GRAVY_NETWORKSTREAM_HPP
#define GRAVY_NETWORKSTREAM_HPP

#include "Socket.hpp"

namespace Gravy::System::Net
{
    class NetworkStream
    {
    private:
        Socket *socket;
    public:
        NetworkStream();
        NetworkStream(Socket *socket);
        ~NetworkStream();
        ssize_t Read(void *buffer, size_t size);
        ssize_t Write(const void *buffer, size_t size);
        void Close();
    };
};

#endif