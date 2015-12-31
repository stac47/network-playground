#ifndef __ADDRESSFACTORY_H__
#define __ADDRESSFACTORY_H__

#include <np/net/SocketConstants.h>
#include <np/net/Address.h>

namespace np {
namespace net {

class AddressFactory
{
public:
    static AddressPtr CreateFromCanonicalAddress(
        const std::string& iAddress,
        uint16_t iPort);

    static AddressPtr CreateEmpty(SocketFamily iFamily);
};

} // namespace net
} // namespace np


#endif /* __ADDRESSFACTORY_H__ */
