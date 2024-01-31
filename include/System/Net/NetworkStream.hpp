#ifndef GRAVY_NETWORKSTREAM_HPP
#define GRAVY_NETWORKSTREAM_HPP

#ifdef GRAVY_USE_OPENSSL

#include "Socket.hpp"
#include "SslStream.hpp"

namespace Gravy::System::Net
{
    class NetworkStream
    {
    private:
        Socket socket;
        SslStream ssl;
        bool secure;
    public:
        NetworkStream()
        {

        }

        NetworkStream(const Socket &socket)
        {
            this->socket = socket;
            secure = false;
        }

        NetworkStream(const Socket &socket, const SslStream &ssl)
        {
            this->socket = socket;
            this->ssl = ssl;
            secure = true;
        }

        int32_t ReadByte()
        {
            if(secure)
                return ssl.ReadByte();
            else
                return socket.ReadByte();
        }

        ssize_t Read(void *buffer, size_t size)
        {
            if(secure)
                return ssl.Read(buffer, size);
            else
                return socket.Read(buffer, size);
        }

        ssize_t Write(const void *buffer, size_t size)
        {
            if(secure)
                return ssl.Write(buffer, size);
            else
                return socket.Write(buffer, size);
        }

        void Close()
        {
            if(secure)
                ssl.Close();
            socket.Close();
        }

        bool IsSecure() const
        {
            return secure;
        }
    };
};

#endif //GRAVY_USE_OPENSSL

#endif