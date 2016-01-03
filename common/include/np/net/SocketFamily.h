#ifndef __SOCKETFAMILY_H__
#define __SOCKETFAMILY_H__

#include <sys/socket.h>

namespace np {
namespace net {

enum class SocketFamily
{
    kIPv4 = AF_INET,
    kIPv6 = AF_INET6
};

} // namespace net
} // namespace np

#endif /* __SOCKETFAMILY_H__ */
