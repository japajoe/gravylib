#ifdef GRAVY_USE_OPENSSL

#include "SslContext.hpp"

namespace Gravy::System::Net
{
    SslContext::SslContext()
    {
        this->context = SSL_CTX_new(TLS_method());
    }

    SslContext::SslContext(SSL_CTX *sslContext)
    {
        this->context = sslContext;
    }

    SslContext::SslContext(const std::string &certificatePath, const std::string &privateKeyPath)
    {
        context = SSL_CTX_new(TLS_server_method());

        if(context == nullptr)
        {
            throw SslException("Failed to create SSL context");
        }
        
        if (SSL_CTX_use_certificate_file(context, certificatePath.c_str(), SSL_FILETYPE_PEM) <= 0) 
        {
            SSL_CTX_free(context);
            context = nullptr;
            throw SslException("Failed to use certificate file");
        }

        if (SSL_CTX_use_PrivateKey_file(context, privateKeyPath.c_str(), SSL_FILETYPE_PEM) <= 0) 
        {
            SSL_CTX_free(context);
            context = nullptr;
            throw SslException("Failed to use private key file");
        }

        if (!SSL_CTX_check_private_key(context)) 
        {
            SSL_CTX_free(context);
            context = nullptr;
            throw SslException("Failed to check private key");
        }
    }

    void SslContext::Dispose()
    {
        if(context)
        {
            SSL_CTX_free(context);
            context = nullptr;
        }
    }

    SSL_CTX *SslContext::GetContext()
    {
        return context;
    }    
};

#endif //GRAVY_USE_OPENSSL