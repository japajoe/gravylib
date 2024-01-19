#ifndef GRAVY_ANTIFORGERY_HPP
#define GRAVY_ANTIFORGERY_HPP

#include "../Guid.hpp"
#include "../DateTime.hpp"
#include <unordered_map>
#include <string>

namespace Gravy::System::Security
{
    class AntiForgeryToken
    {
    public:
        Guid token;
        DateTime expires;
    };

    class AntiForgery
    {
    private:
        static std::unordered_map<std::string,AntiForgeryToken> tokens;
        static void InvalidateTokens();
    public:
        static Guid GenerateToken(DateTime expires);
        static bool IsValidToken(const Guid &token);
        static void InvalidateToken(const Guid &token);
    };
};

#endif