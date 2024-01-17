#include "TcpClient.hpp"

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

    bool TcpClient::Connect(const std::string &ip, uint16_t port)
    {
        if(socket.GetFileDescriptor() >= 0)
            return false;

        socket = Socket(SocketType::Stream, AddressFamily::AFInet);

        if(!socket.Connect(ip, port))
        {
            socket.Close();
            return false;
        }

        return true;
    }

    Socket *TcpClient::GetSocket()
    {
        return &socket;
    }
}