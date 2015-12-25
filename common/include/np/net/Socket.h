#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <memory>

namespace np {
namespace net {

class Socket
{
    int fd_;
    std::string localAddress_;
    std::string localPort_;

public:
    Socket() = delete;
    Socket(int iFamily, int iType);
    virtual ~Socket() {}

    void connect(const std::string& iAddress,
                 const std::string& iPort);

    void bind(const std::string& iAddress,
              const std::string& iPort);

    void listen(int iBacklog);

    Socket accept();

    void close();
};

typedef std::shared_ptr<Socket> SocketPtr;

} // namespace net
} // namespace np
#endif /* __SOCKET_H__ */
