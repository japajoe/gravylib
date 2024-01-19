#include "AntiForgery.hpp"

namespace Gravy::System::Security
{
    std::unordered_map<std::string,AntiForgeryToken> AntiForgery::tokens;

    Guid AntiForgery::GenerateToken(DateTime expires)
    {
        InvalidateTokens();

        AntiForgeryToken token;
        token.expires = expires;
        token.token = Guid::NewGuid();
        tokens[token.token.ToString()] = token;
        return token.token;
    }

    bool AntiForgery::IsValidToken(const Guid &token)
    {
        bool result = false;
        std::string uuid = token.ToString();
        DateTime now = DateTime::Now();

        if(tokens.count(uuid) > 0)
        {
            auto &t = tokens[uuid];

            if(now >= t.expires)
            {
                tokens.erase(uuid);
                result = false;
            }
            else
            {
                result = true;
            }
        }
        
        InvalidateTokens();
        
        return result;
    }

    void AntiForgery::InvalidateToken(const Guid &token)
    {
        std::string uuid = token.ToString();

        if(tokens.count(uuid) > 0)
        {
            tokens.erase(uuid);
        }
    }

    void AntiForgery::InvalidateTokens()
    {
        DateTime now = DateTime::Now();

        for(auto &t : tokens)
        {
            if(now >= t.second.expires)
                tokens.erase(t.first);
        }
    }
};