#include <np/net/AddressFactory.h>

namespace np {
namespace net {

AddressPtr AddressFactory::CreateAddress(
    SocketFamily iFamily,
    const std::string& iAddress,
    uint16_t iPort)
{
    AddressPtr ret = nullptr;
    switch(iFamily)
    {
    case SocketFamily::kIPv4:
        ret = std::make_shared<AddressIPv4>(iAddress, iPort);
        break;
    case SocketFamily::kIPv6:
        /* ret = std::make_shared<AddressIPv6>(); */
        break;
    }
    return ret;
}

AddressPtr AddressFactory::CreateEmpty(SocketFamily iFamily)
{
    AddressPtr ret = nullptr;
    switch(iFamily)
    {
    case SocketFamily::kIPv4:
        ret = std::make_shared<AddressIPv4>();
        break;
    case SocketFamily::kIPv6:
        /* ret = std::make_shared<AddressIPv6>(); */
        break;
    }
    return ret;
}

} // namespace net
} // namespace np
