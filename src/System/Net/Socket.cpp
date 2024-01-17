#include "Socket.hpp"

#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif

namespace Gravy::System::Net
{
#ifdef _WIN32
    static bool winsockInitialized = false;
#endif

    static void InitializeWinsock2()
    {
    #ifdef _WIN32
        if(winsockInitialized)
            return;
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) 
        {
            printf("Failed to initialize winsock\n")
            winsockInitialized = true;
        }
    #endif        
    }

    Socket::Socket()
    {
        InitializeWinsock2();
        std::memset(&s, 0, sizeof(gravy_socket_t));
        s.fd = -1;
    }

    Socket::Socket(Socket *socket)
    {
        InitializeWinsock2();
        std::memcpy(this, socket, sizeof(Socket));
    }

    Socket::Socket(SocketType type, AddressFamily addressFamily)
    {
        InitializeWinsock2();
        std::memset(&s, 0, sizeof(gravy_socket_t));

        int socketType = SOCK_STREAM;

        switch(type)
        {
            case SocketType::Dgram:
                socketType = SOCK_DGRAM;
                break;
            case SocketType::Raw:
                socketType = SOCK_RAW;
                break;
            case SocketType::Stream:
                socketType = SOCK_STREAM;
                break;
            default:
                socketType = SOCK_STREAM;
                break;
        }

        s.fd = socket(static_cast<int>(addressFamily), socketType, 0);
    #ifdef _WIN32
        if(s.fd == INVALID_SOCKET)
            s.fd = -1;
    #endif
    }

    void Socket::Close()
    {
    #ifdef _WIN32
        closesocket(s.fd);
    #else
        close(s.fd);
    #endif
        s.fd = -1;
    }
    
    bool Socket::Bind(const std::string &bindAddress, uint16_t port)
    {
        sockaddr_in_t address = {0};
        address.sin_family = AF_INET;

        struct in_addr addr;

        if (inet_pton(AF_INET, bindAddress.c_str(), &addr) <= 0)
            return false;

        address.sin_addr.s_addr = INADDR_ANY;
        std::memcpy(&address.sin_addr.s_addr, &addr, sizeof(addr));
        
        address.sin_port = htons(port);

        std::memcpy(&s.address.ipv4, &address, sizeof(sockaddr_in_t));

        return bind(s.fd, (struct sockaddr*)&s.address.ipv4, sizeof(sockaddr_in_t)) == SOCKET_ERROR ? false : true;
    }

    bool Socket::Connect(const std::string &ip, uint16_t port)
    {
        struct sockaddr_in serverAddr = {0};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
        return connect(s.fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR ? false : true;
    }

    bool Socket::Listen(int32_t backlog)
    {
        return listen(s.fd, backlog) == SOCKET_ERROR ? false : true;
    }

    bool Socket::Accept(Socket &socket)
    {
        sockaddr_in_t clientAddr;
        uint32_t addrLen = sizeof(clientAddr);

        int clientFD = -1;

    #ifdef _WIN32
        clientFD = accept(s.fd, (struct sockaddr*)&clientAddr, (int32_t*)&addrLen);
        
        if(clientFD == INVALID_SOCKET)
            clientFD = -1;
    #else
        clientFD = accept(s.fd, (struct sockaddr*)&clientAddr, &addrLen);
    #endif

        if (clientFD == -1)
            return false;

        socket.s.fd = clientFD;
        std::memcpy(&socket.s.address, &clientAddr, sizeof(sockaddr_in_t));

        return true;
    }

    bool Socket::SetOption(int level, int option, const void *value, uint32_t valueSize)
    {
    #ifdef _WIN32
        return setsockopt(s.fd, level, option, (char*)value, valueSize) != 0 ? false : true;
    #else
        return setsockopt(s.fd, level, option, value, valueSize) != 0 ? false : true;
    #endif
    }

    int32_t Socket::ReadByte()
    {
        unsigned char b = 0;
    #ifdef _WIN32
        if(recv(s.fd, (char*)b, 1, 0) > 0)
            return static_cast<int32_t>(b);
    #else
        if(recv(s.fd, &b, 1, 0) > 0)
            return static_cast<int32_t>(b);
    #endif
        return -1;
    }

    ssize_t Socket::Read(void *buffer, size_t size)
    {
    #ifdef _WIN32
        return recv(s.fd, (char*)buffer, size, 0);
    #else
        return recv(s.fd, buffer, size, 0);
    #endif
    }

    ssize_t Socket::Write(const void *buffer, size_t size)
    {
    #ifdef _WIN32
        return send(s.fd, (char*)data, size, 0);
    #else
        return send(s.fd, buffer, size, 0);
    #endif
    }

    int32_t Socket::GetFileDescriptor() const
    {
        return s.fd;
    }
};