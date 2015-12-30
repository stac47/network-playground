#ifndef __SOCKETCONSTANTS_H__
#define __SOCKETCONSTANTS_H__

#include <sys/socket.h>

namespace np {
namespace net {

enum class SocketFamily
{
    kIPv4 = AF_INET,
    kIPv6 = AF_INET6
};

enum class SocketType
{
    kTCP = SOCK_STREAM,
    kUDP = SOCK_DGRAM,
    kRAW = SOCK_RAW
};

} // namespace net
} // namespace np
#endif /* __SOCKETCONSTANTS_H__ */
