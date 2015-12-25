#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <memory>

namespace np {
namespace net {

class Socket;

typedef std::shared_ptr<Socket> SocketPtr;

class Socket
{
    int fd_;
    bool opened_;
    bool closed_;

    std::string localAddress_;
    std::string localPort_;

public:
    Socket() = delete;
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    static SocketPtr Create(int iFamily, int iType);

    virtual ~Socket();

    void connect(const std::string& iAddress,
                 const std::string& iPort);

    void bind(const std::string& iAddress,
              const std::string& iPort);

    void listen(int iBacklog);

    SocketPtr accept();

    void close();
protected:
    Socket(int iFamily, int iType);
};


} // namespace net
} // namespace np
#endif /* __SOCKET_H__ */
