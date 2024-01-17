#include "TcpListener.hpp"
#include "Console.hpp"

namespace Gravy::System::Net
{
    TcpListener::TcpListener(const std::string &bindAddress, uint16_t port, int32_t backlog)
    {
        this->bindAddress = bindAddress;
        this->port = port;
        this->backlog = backlog;
    }

    bool TcpListener::Start()
    {
        if(listener.GetFileDescriptor() >= 0)
        {
            Console::WriteError("Socket already in use");
            return false;
        }

        listener = Socket(SocketType::Stream, AddressFamily::AFInet);

        int reuse = 1;

        if(!listener.SetOption(SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
        {
            Console::WriteError("Failed to set socket option");
            listener.Close();
            return false;
        }
        
        if(!listener.Bind(bindAddress, port))
        {
            Console::WriteError("Failed to bind socket");
            listener.Close();
            return false;
        }

        if(!listener.Listen(backlog))
        {
            Console::WriteError("Failed to start listening");
            listener.Close();
            return false;
        }

        return true;
    }

    bool TcpListener::Accept(TcpClient &client)
    {
        if(listener.GetFileDescriptor() < 0)
            return false;

        Socket clientSocket;

        if(listener.Accept(clientSocket))
        {
            client = TcpClient(clientSocket);
            return true;
        }

        return false;
    }

    void TcpListener::Close()
    {
        if(listener.GetFileDescriptor() >= 0)
            listener.Close();
    }
};