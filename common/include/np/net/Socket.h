#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <memory>

#include <np/net/SocketType.h>
#include <np/net/Address.h>

namespace np {
namespace net {

template<typename A>
class Socket
{
public:
    Socket() = delete;
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    virtual ~Socket();

    static std::shared_ptr<Socket<A>> Create(SocketType iType);

    void connect(const A& iAddr);
    void bind(const A& iAddr);
    void listen(int iBacklog);
    std::shared_ptr<Socket<A>> accept();
    void close();

    ssize_t read(char* oBuffer, size_t iLen);
    ssize_t write(const char* iBuffer, size_t iLen);

    int getFd() const;
    std::shared_ptr<A> getLocalAddress() const;
    std::shared_ptr<A> getRemoteAddress() const;

protected:
    explicit Socket(int iFileDescriptor);
    Socket(SocketType iType);

private:
    int fd_;

    SocketType type_;

    bool opened_;
    bool closed_;
};

template class Socket<AddressIPv4>;

} // namespace net
} // namespace np
#endif /* __SOCKET_H__ */
