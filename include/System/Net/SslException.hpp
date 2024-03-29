#ifndef GRAVY_SSLEXCEPTION_HPP
#define GRAVY_SSLEXCEPTION_HPP

#ifdef GRAVY_USE_OPENSSL

#include <exception>
#include <string>

namespace Gravy::System::Net
{
    class SslException : public std::exception 
    {
    public:
        SslException(const char* message) : message_(message) {}

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