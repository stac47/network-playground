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

class AddressIPv4 : public Address
{
public:
    static int GetFamily();

    AddressIPv4(const std::string& iAddr, uint16_t iPort);
    AddressIPv4();

    ::sockaddr* sockaddr() override;
    const ::sockaddr* sockaddr() const override;
    socklen_t getLength() const override;
    const std::string getAddress() const;
    uint16_t getPort() const;
    const std::string toString() const override;

private:
    ::sockaddr_in rawAddress_;
};


} // namespace net
} // namespace np
#endif /* __ADDRESS_H__ */
