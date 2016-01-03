#ifndef __SOCKETTYPE_H__
#define __SOCKETTYPE_H__

#include <sys/socket.h>

namespace np {
namespace net {

enum class SocketType
{
    kTCP = SOCK_STREAM,
    kUDP = SOCK_DGRAM,
    kRAW = SOCK_RAW
};

} // namespace net
} // namespace np
#endif /* __SOCKETTYPE_H__ */
