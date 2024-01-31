#ifndef GRAVY_HTTPCLIENT_HPP
#define GRAVY_HTTPCLIENT_HPP

#ifdef GRAVY_USE_OPENSSL

#include <string>
#include <exception>
#include <functional>
#include "SslContext.hpp"

namespace Gravy::System::Net
{
    using HttpClientResponseHandler = std::function<void(void *buffer, size_t size, void *userData)>;

    class HttpClient
    {
    private:
        SslContext sslContext;
        HttpClientResponseHandler responseHandler;
        void *userData;
    public:
        HttpClient();
        ~HttpClient();
        void SetResponseHandler(const HttpClientResponseHandler &handler, void *userData = nullptr);
        void Get(const std::string &url);
        void Close();
    };

    class HttpClientException : public std::exception 
    {
    public:
        HttpClientException(const char* message) : message_(message) {}

        const char* what() const noexcept override 
        {
            return message_.c_str();
        }
    private:
        std::string message_;
    };
};

#endif //GRAVY_USE_OPENSSL

#endif