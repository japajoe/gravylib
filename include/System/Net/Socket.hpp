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

#ifdef _WIN32
    enum class AddressFamily : int
    {
        AFUnspec = AF_UNSPEC,
        AFUnix = AF_UNIX,
        AFInet = AF_INET,
        AFImplink = AF_IMPLINK,
        AFPup = AF_PUP,
        AFChaos = AF_CHAOS,
        AFNs = AF_NS,
        AFIpx = AF_IPX,
        AFIso = AF_ISO,
        AFOsi = AF_OSI,
        AFEcma = AF_ECMA,
        AFDatakit = AF_DATAKIT,
        AFCcitt = AF_CCITT,
        AFSna = AF_SNA,
        AFDecnet = AF_DECnet,
        AFDli = AF_DLI,
        AFLat = AF_LAT,
        AFHylink = AF_HYLINK,
        AFAppletalk = AF_APPLETALK,
        AFNetbios = AF_NETBIOS,
        AFVoiceview = AF_VOICEVIEW,
        AFFirefox = AF_FIREFOX,
        AFUnknown1 = AF_UNKNOWN1,
        AFBan = AF_BAN,
        AFAtm = AF_ATM,
        AFInet6 = AF_INET6,
        AFCluster = AF_CLUSTER,
        AF12844 = AF_12844,
        AFIrda = AF_IRDA,
        AFNetdes = AF_NETDES,
        AFTcnprocess = AF_TCNPROCESS,
        AFTcnmessage = AF_TCNMESSAGE,
        AFIclfxbm = AF_ICLFXBM,
        AFBth = AF_BTH,
        AFMax = AF_MAX
    };
#else
    enum class AddressFamily : int
    {
        AFLocal = AF_LOCAL,
        AFUnix = AF_UNIX,
        AFFile = AF_FILE,
        AFInet = AF_INET,
        AFAx25 = AF_AX25,
        AFIpx = AF_IPX,
        AFAppletalk = AF_APPLETALK,
        AFNetrom = AF_NETROM,
        AFBridge = AF_BRIDGE,
        AFAtmpvc = AF_ATMPVC,
        AFX25 = AF_X25,
        AFInet6 = AF_INET6,
        AFRose = AF_ROSE,
        AFDecnet = AF_DECnet,
        AFNetbeui = AF_NETBEUI,
        AFSecurity = AF_SECURITY,
        AFKey = AF_KEY,
        AFNetlink = AF_NETLINK,
        AFRoute = AF_ROUTE,
        AFPacket = AF_PACKET,
        AFAsh = AF_ASH,
        AFEconet = AF_ECONET,
        AFAtmsvc = AF_ATMSVC,
        AFRds = AF_RDS,
        AFSna = AF_SNA,
        AFIrda = AF_IRDA,
        AFPppox = AF_PPPOX,
        AFWanpipe = AF_WANPIPE,
        AFLlc = AF_LLC,
        AFIb = AF_IB,
        AFMpls = AF_MPLS,
        AFCan = AF_CAN,
        AFTipc = AF_TIPC,
        AFBluetooth = AF_BLUETOOTH,
        AFIucv = AF_IUCV,
        AFRxrpc = AF_RXRPC,
        AFIsdn = AF_ISDN,
        AFPhonet = AF_PHONET,
        AFIeee802154 = AF_IEEE802154,
        AFCaif = AF_CAIF,
        AFAlg = AF_ALG,
        AFNfc = AF_NFC,
        AFVsock = AF_VSOCK,
        AFKcm = AF_KCM,
        AFQipcrtr = AF_QIPCRTR,
        AFSmc = AF_SMC,
        AFXdp = AF_XDP,
        AFMax = AF_MAX
    };
#endif

    class Socket
    {
    private:
        gravy_socket_t s;
    public:
        Socket();
        Socket(SocketType type, AddressFamily addressFamily);
        void Close();
        bool Bind(const std::string &address, uint16_t port);
        bool Connect(const std::string &ip, uint16_t port);
        bool Listen(int32_t backlog);
        bool Accept(Socket &socket);
        bool SetOption(int level, int option, const void *value, uint32_t valueSize);
        ssize_t Read(void *buffer, size_t size);
        ssize_t Write(const void *buffer, size_t size);
        int32_t GetFileDescriptor() const;
    };
};

#endif