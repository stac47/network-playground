#include <np/net/AddressFactory.h>

namespace np {
namespace net {

AddressPtr AddressFactory::CreateFromCanonicalAddress(
    const std::string& iAddress,
    uint16_t iPort)
{
    return nullptr;
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
