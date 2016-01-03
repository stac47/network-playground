#include <string>
#include <cstring>
#include <memory>
#include <sstream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <np/net/SocketFamily.h>
#include <np/net/SocketType.h>

#include <np/net/Address.h>

namespace np {
namespace net {

Address::Address(SocketFamily iFamily)
  : family_(iFamily)
{}

SocketFamily Address::getFamily() const
{
    return family_;
}

AddressIPv4::AddressIPv4()
  : Address(SocketFamily::kIPv4)
{
    std::memset(&rawAddress_, 0, sizeof(rawAddress_));
}

AddressIPv4::AddressIPv4(const std::string& iAddr, uint16_t iPort)
  : Address(SocketFamily::kIPv4)
{
    std::memset(&rawAddress_, 0, sizeof(rawAddress_));
    rawAddress_.sin_family = static_cast<int>(AF_INET);
    if (iAddr.empty())
    {
        rawAddress_.sin_addr.s_addr = ::htonl(INADDR_ANY);
    }
    else
    {
        ::inet_pton(AF_INET, iAddr.c_str(), &rawAddress_.sin_addr.s_addr);
    }
    rawAddress_.sin_port = htons(iPort);
}

uint8_t AddressIPv4::getLength() const
{
    return sizeof(sockaddr_in);
}

::sockaddr* AddressIPv4::sockaddr()
{
    return reinterpret_cast<::sockaddr*>(&rawAddress_);
}

const std::string AddressIPv4::getAddress() const
{

    char address[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &rawAddress_.sin_addr, address, sizeof(address));
    return std::string(address);
}

uint16_t AddressIPv4::getPort() const
{
    return ntohs(rawAddress_.sin_port);
}

const std::string AddressIPv4::toString() const
{
    std::stringstream ss;
    ss << getAddress() << ":" << getPort();
    return ss.str();
}

} // namespace net
} // namespace np
