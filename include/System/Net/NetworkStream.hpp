#ifndef GRAVY_NETWORKSTREAM_HPP
#define GRAVY_NETWORKSTREAM_HPP

#include "Socket.hpp"
#include "SslStream.hpp"

namespace Gravy::System::Net
{
    class NetworkStream
    {
    private:
        Socket socket;
    #ifdef GRAVY_USE_OPENSSL
        SslStream ssl;
        bool secure;
    #endif
    public:
        NetworkStream()
        {

        }

        NetworkStream(const Socket &socket)
        {
            this->socket = socket;
        #ifdef GRAVY_USE_OPENSSL
            secure = false;
        #endif
        }

    #ifdef GRAVY_USE_OPENSSL
        NetworkStream(const Socket &socket, const SslStream &ssl)
        {
            this->socket = socket;
            this->ssl = ssl;
            secure = true;
        }
    #endif

        int32_t ReadByte()
        {
        #ifdef GRAVY_USE_OPENSSL
            if(secure)
                return ssl.ReadByte();
            else
                return socket.ReadByte();
        #else
            return socket.ReadByte();
        #endif
        }

        ssize_t Read(void *buffer, size_t size)
        {
        #ifdef GRAVY_USE_OPENSSL
            if(secure)
                return ssl.Read(buffer, size);
            else
                return socket.Read(buffer, size);
        #else
            return socket.Read(buffer, size);
        #endif
        }

        ssize_t Write(const void *buffer, size_t size)
        {
        #ifdef GRAVY_USE_OPENSSL
            if(secure)
                return ssl.Write(buffer, size);
            else
                return socket.Write(buffer, size);
        #else
            return socket.Write(buffer, size);
        #endif
        }

        void Close()
        {
        #ifdef GRAVY_USE_OPENSSL
            if(secure)
                ssl.Close();
        #endif
            socket.Close();
        }

    #ifdef GRAVY_USE_OPENSSL
        bool IsSecure() const
        {
            return secure;
        }
    #endif
    };
};

#endif