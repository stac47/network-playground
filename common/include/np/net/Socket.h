#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <memory>

#include <np/net/SocketFamily.h>
#include <np/net/SocketType.h>
#include <np/net/Address.h>

namespace np {
namespace net {

class Socket;

typedef std::shared_ptr<Socket> SocketPtr;

class Socket
{
public:
    Socket() = delete;
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    virtual ~Socket();

    static SocketPtr Create(SocketFamily iFamily, SocketType iType);

    void connect(const AddressPtr& iAddr);

    void bind(const AddressPtr& iAddr);

    void listen(int iBacklog);

    SocketPtr accept();

    void close();

    ssize_t read(char* oBuffer, size_t iLen);
    ssize_t write(const char* iBuffer, size_t iLen);

    int getFd() const;

protected:
    explicit Socket(int iFileDescriptor);
    Socket(SocketFamily iFamily, SocketType iType);

private:
    int fd_;

    SocketFamily family_;
    SocketType type_;

    bool opened_;
    bool closed_;
};


} // namespace net
} // namespace np
#endif /* __SOCKET_H__ */
