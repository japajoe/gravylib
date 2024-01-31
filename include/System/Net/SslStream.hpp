#ifndef GRAVY_SSLSTREAM_HPP
#define GRAVY_SSLSTREAM_HPP

#ifdef GRAVY_USE_OPENSSL

#include "Socket.hpp"
#include "SslContext.hpp"
#include "SslException.hpp"
#include <openssl/ssl.h>

namespace Gravy::System::Net
{
    class SslStream
    {
    private:
        SSL *ssl;
    public:
        SslStream();
        //Used to create an SslStream for incoming connections
        SslStream(Socket *socket, SslContext *sslContext);
        //Used to create an SslStream for outgoing connections
        SslStream(Socket *socket, SslContext *sslContext, const char *hostName);
        int32_t ReadByte();
        ssize_t Read(void *buffer, size_t size);
        ssize_t Write(const void *buffer, size_t size);
        void Close();
    };
};

#endif //GRAVY_USE_OPENSSL

#endif