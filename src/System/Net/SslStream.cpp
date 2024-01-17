#include "System/Net/SslStream.hpp"
#include <exception>

#ifdef GRAVY_USE_OPENSSL
namespace Gravy::System::Net
{
    SslStream::SslStream()
    {
        this->ssl = nullptr;
    }

    SslStream::SslStream(Socket *socket, SslContext *sslContext)
    {
        if(sslContext)
        {
            ssl = SSL_new(sslContext->GetContext());

            if(ssl == nullptr)
                throw SslException("Failed to create SSL instance");

            SSL_set_fd(ssl, socket->GetFileDescriptor());

            if (SSL_accept(ssl) <= 0) 
            {
                SSL_shutdown(ssl);
                SSL_free(ssl);
                ssl = nullptr;
                throw SslException("Failed to SSL accept");
            }
        }
    }

    SslStream::SslStream(Socket *socket, SslContext *sslContext, const char *hostName)
    {
        if(sslContext)
        {
            ssl = SSL_new(sslContext->GetContext());

            if(ssl == nullptr)
                throw SslException("Failed to create SSL instance");

            SSL_set_fd(ssl, socket->GetFileDescriptor());
            
            if(hostName)
                SSL_ctrl(ssl, SSL_CTRL_SET_TLSEXT_HOSTNAME, TLSEXT_NAMETYPE_host_name, (void*)hostName);

            if (SSL_connect(ssl) != 1) 
            {
                SSL_shutdown(ssl);
                SSL_free(ssl);
                ssl = nullptr;
                throw SslException("Failed to SSL connect");
            }
        }
    }

    int32_t SslStream::ReadByte()
    {
        if(!ssl)
            return -1;
        unsigned char b = 0;
        if(SSL_read(ssl, &b, 1) > 0)
            return static_cast<int32_t>(b);
        return -1;
    }

    ssize_t SslStream::Read(void *buffer, size_t size)
    {
        if(ssl)
            return SSL_read(ssl, buffer, size);
        return 0;
    }

    ssize_t SslStream::Write(const void *buffer, size_t size)
    {
        if(ssl)
            return SSL_write(ssl, buffer, size);
        return 0;
    }

    void SslStream::Close()
    {
        if(ssl)
        {
            SSL_shutdown(ssl);
            SSL_free(ssl);
            ssl = nullptr;
        }
    }
};
#endif //GRAVY_USE_OPENSSL