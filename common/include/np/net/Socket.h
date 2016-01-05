#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <memory>

#include <np/net/SocketType.h>
#include <np/net/SocketInterface.h>
#include <np/net/AddressIPv4.h>

namespace np {
namespace net {

template<typename A>
class Socket final : public SocketInterface
{
public:
    Socket() = delete;
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    virtual ~Socket();

    static std::shared_ptr<Socket<A>> Create(SocketType iType);

    void connect(const A& iAddr);
    void bind(const A& iAddr);
    std::shared_ptr<Socket<A>> accept();

    std::shared_ptr<A> getLocalAddress() const;
    std::shared_ptr<A> getRemoteAddress() const;

protected:
    explicit Socket(SocketType iType, int iFileDescriptor);
    explicit Socket(SocketType iType);
};

template class Socket<AddressIPv4>;

} // namespace net
} // namespace np
#endif /* __SOCKET_H__ */
