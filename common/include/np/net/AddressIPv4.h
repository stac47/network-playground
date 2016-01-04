#ifndef __ADDRESSIPV4_H__
#define __ADDRESSIPV4_H__
#include <memory>

#include <sys/socket.h>
#include <netinet/in.h>

#include <np/net/Address.h>
#include <np/net/SocketType.h>

namespace np {
namespace net {

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

#endif /* __ADDRESSIPV4_H__ */
