#ifndef GRAVY_HOSTINFO_HPP
#define GRAVY_HOSTINFO_HPP

#include <string>
#include <cstdint>

namespace Gravy::System::Net
{
    class HostInfo
    {
    public:
        std::string name;
        std::string ip;
        uint16_t port;
        HostInfo();
        HostInfo(const std::string &name, const std::string &ip, uint16_t port);
        static bool Resolve(const std::string &url, HostInfo &hostInfo);
        static bool GetIPAndPort(const std::string &url, std::string &ip, uint16_t &port, bool https);
    };
};

#endif