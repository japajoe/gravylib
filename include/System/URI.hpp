#ifndef GRAVY_URI_HPP
#define GRAVY_URI_HPP

#include <string>

namespace Gravy::System
{
    class URI
    {
    private:
        std::string uri;
    public:
        URI(const std::string &uriString);
        bool GetScheme(std::string &value);
        bool GetHost(std::string &value);
        bool GetPath(std::string &value);
        bool GetQuery(std::string &value);
        bool GetFragment(std::string &value);
    };
};

#endif