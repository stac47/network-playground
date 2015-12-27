#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <memory>

#include <sys/socket.h>

namespace np {
namespace net {

enum class SocketFamily
{
    kIPv4 = AF_INET,
    kIPv6 = AF_INET6
};

enum class SocketType
{
    kTCP = SOCK_STREAM,
    kUDP = SOCK_DGRAM,
    kRAW = SOCK_RAW
};

enum class SocketProtocol
{
    kDefault = 0
};

class Socket;

typedef std::shared_ptr<Socket> SocketPtr;

class Socket
{
    int fd_;

    SocketFamily family_;
    SocketType type_;
    SocketProtocol protocol_;

    bool opened_;
    bool closed_;

public:
    Socket() = delete;
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    static SocketPtr Create(SocketFamily iFamily,
                            SocketType iType,
                            SocketProtocol iProtocol = SocketProtocol::kDefault);

    virtual ~Socket();

    void connect(const std::string& iAddress,
                 const std::string& iPort);

    void bind(const std::string& iAddress,
              const std::string& iPort);

    void listen(int iBacklog);

    SocketPtr accept();

    void close();

    ssize_t read(char* oBuffer, size_t iLen);

    ssize_t write(const char* iBuffer, size_t iLen);

protected:
    explicit Socket(int iFileDescriptor);
    Socket(SocketFamily iFamily,
           SocketType iType,
           SocketProtocol iProtocol = SocketProtocol::kDefault);
};


} // namespace net
} // namespace np
#endif /* __SOCKET_H__ */
