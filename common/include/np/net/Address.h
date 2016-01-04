#ifndef __ADDRESS_H__
#define __ADDRESS_H__

#include <memory>

#include <sys/socket.h>
#include <netinet/in.h>

#include <np/net/SocketType.h>

namespace np {
namespace net {

class Address;

typedef std::shared_ptr<Address> AddressPtr;

class Address
{
public:
    virtual socklen_t getLength() const = 0;
    virtual ::sockaddr* sockaddr() = 0;
    virtual const ::sockaddr* sockaddr() const = 0;
    virtual const std::string toString() const = 0;
};

} // namespace net
} // namespace np
#endif /* __ADDRESS_H__ */
