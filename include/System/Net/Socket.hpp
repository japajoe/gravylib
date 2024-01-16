#ifndef GRAVY_SOCKET_HPP
#define GRAVY_SOCKET_HPP

#include <string>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0600
#endif

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

namespace Gravy::System::Net
{
    typedef struct sockaddr_in sockaddr_in_t;
    typedef struct sockaddr_in6 sockaddr_in6_t;

    typedef union {
        sockaddr_in_t ipv4;
        sockaddr_in6_t ipv6;
    } gravy_socket_address;

    typedef struct gravy_socket {
        int32_t fd;
        gravy_socket_address address;
    } gravy_socket_t;

    enum class SocketType
    {
        Stream,
        Dgram,
        Raw
    };

    class Socket
    {
    private:
        gravy_socket_t s;
    public:
        Socket();
        Socket(SocketType type);
        bool Bind(const std::string &address, uint16_t port);
        bool Connect(const std::string &ip, uint16_t port);
        bool Listen(int32_t backlog);
        bool Accept(Socket &socket);
        bool SetOption(int level, int option, const void *value, uint32_t valueSize);
        ssize_t Read(void *buffer, size_t size);
        ssize_t Write(const void *buffer, size_t size);
        void Close();
        int32_t GetFileDescriptor() const;
    };
};

#endif