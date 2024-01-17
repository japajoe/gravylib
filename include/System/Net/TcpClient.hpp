#ifndef GRAVY_TCPCLIENT_HPP
#define GRAVY_TCPCLIENT_HPP

#include "System/Net/Socket.hpp"
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
        void Close();
        Socket *GetSocket();
    };
};

#endif