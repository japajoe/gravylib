#ifndef GRAVY_TCPCLIENT_HPP
#define GRAVY_TCPCLIENT_HPP

#include "Socket.hpp"
#include <cstdint>
#include <string>

namespace Gravy::System::Net
{
    class TcpClient
    {
    private:
        Socket socket;
    public:
        TcpClient();
        TcpClient(const Socket &socket);
        bool Connect(const std::string &ip, uint16_t port);
        void Close();
        Socket *GetSocket();
    };
};

#endif