#ifndef GRAVY_SSLCONTEXT_HPP
#define GRAVY_SSLCONTEXT_HPP

#ifdef GRAVY_USE_OPENSSL

#include "SslException.hpp"
#include <string>
#include <openssl/ssl.h>

namespace Gravy::System::Net
{
    class SslContext
    {
    private:
        SSL_CTX *context;
    public:
        SslContext();
        SslContext(SSL_CTX *sslContext);
        SslContext(const std::string &certificatePath, const std::string &privateKeyPath);
        void Dispose();
        SSL_CTX *GetContext();
    };
};

#endif //GRAVY_USE_OPENSSL

#endif