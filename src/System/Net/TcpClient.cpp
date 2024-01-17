#include "System/Net/TcpClient.hpp"

namespace Gravy::System::Net
{
    TcpClient::TcpClient()
    {

    }

    TcpClient::TcpClient(const Socket &socket)
    {
        this->socket = socket;
    }

    void TcpClient::Close()
    {
        if(socket.GetFileDescriptor() >= 0)
            socket.Close();
    }

    Socket *TcpClient::GetSocket()
    {
        return &socket;
    }
}