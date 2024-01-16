#ifndef GRAVY_SSLSTREAM_HPP
#define GRAVY_SSLSTREAM_HPP

#ifdef GRAVY_USE_OPENSSL
#include "System/Net/Socket.hpp"
#include "System/Net/SslContext.hpp"
#include "System/Net/SslException.hpp"
#include <openssl/ssl.h>

namespace Gravy::System::Net
{
    class SslStream
    {
    private:
        SSL *ssl;
    public:
        SslStream();
        SslStream(Socket socket, SslContext *sslContext, const char *hostName = nullptr);
        ssize_t Read(void *buffer, size_t size);
        ssize_t Write(const void *buffer, size_t size);
        void Close();
    };
};
#endif //GRAVY_USE_OPENSSL

#endif