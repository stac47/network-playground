#include <string>
#include <cstring>
#include <memory>
#include <sstream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <np/net/SocketType.h>

#include <np/net/Address.h>
#include <np/net/AddressIPv4.h>

namespace np {
namespace net {

int AddressIPv4::GetFamily()
{
    return AF_INET;
}

AddressIPv4::AddressIPv4()
{
    std::memset(&rawAddress_, 0, sizeof(rawAddress_));
}

AddressIPv4::AddressIPv4(const std::string& iAddr, uint16_t iPort)
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

socklen_t AddressIPv4::getLength() const
{
    return sizeof(::sockaddr_in);
}

::sockaddr* AddressIPv4::sockaddr()
{
    return reinterpret_cast<::sockaddr*>(&rawAddress_);
}

const ::sockaddr* AddressIPv4::sockaddr() const
{
    return reinterpret_cast<const ::sockaddr*>(&rawAddress_);
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
