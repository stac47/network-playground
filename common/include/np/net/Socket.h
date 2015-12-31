#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <memory>

#include <np/net/SocketConstants.h>
#include <np/net/Address.h>

namespace np {
namespace net {

class Socket;

typedef std::shared_ptr<Socket> SocketPtr;

class Socket
{
    int fd_;

    SocketFamily family_;
    SocketType type_;

    bool opened_;
    bool closed_;

public:
    Socket() = delete;
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    static SocketPtr Create(SocketFamily iFamily,
                            SocketType iType);

    virtual ~Socket();

    void connect(const AddressPtr& iAddr);

    void bind(const AddressPtr& iAddr);

    void listen(int iBacklog);

    SocketPtr accept();

    void close();

    ssize_t read(char* oBuffer, size_t iLen);

    ssize_t write(const char* iBuffer, size_t iLen);

protected:
    explicit Socket(int iFileDescriptor);
    Socket(SocketFamily iFamily,
           SocketType iType);
};


} // namespace net
} // namespace np
#endif /* __SOCKET_H__ */
