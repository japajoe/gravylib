#ifndef GRAVY_TCPLISTENER_HPP
#define GRAVY_TCPLISTENER_HPP

#include "System/Net/Socket.hpp"
#include "System/Net/TcpClient.hpp"
#include <cstdint>
#include <string>

namespace Gravy::System::Net
{
    class TcpListener
    {
    private:
        Socket listener;
        std::string bindAddress;
        uint16_t port;
        int32_t backlog;
    public:
        TcpListener();
        TcpListener(const std::string &bindAddress, uint16_t port, int32_t backlog);
        bool Start();
        bool Accept(TcpClient &client);
        void Close();
    };
};

#endif