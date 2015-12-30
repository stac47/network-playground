#ifndef __ADDRESS_H__
#define __ADDRESS_H__

#include <memory>

#include <sys/socket.h>

#include <np/net/SocketConstants.h>

namespace np {
namespace net {

class Address
{
public:
    Address(SocketFamily iFamily);

    SocketFamily getFamily() const;
    virtual uint8_t getLength() const = 0;
private:
    SocketFamily family_;
};

class AddressIPv4 : public Address
{
public:
    AddressIPv4(const std::string& iAddr, uint16_t iPort);
    AddressIPv4();

    ::sockaddr* sockaddr();
    uint8_t getLength() const override;
    const std::string& getAddress();
    uint16_t getPort() const;
private:
    sockaddr_in rawAddress_;
    std::string strAddress_;
};


} // namespace net
} // namespace np
#endif /* __ADDRESS_H__ */
