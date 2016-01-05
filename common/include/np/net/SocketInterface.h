#ifndef __SOCKETINTERFACE_H__
#define __SOCKETINTERFACE_H__

#include <string>
#include <memory>

#include <np/net/SocketType.h>

namespace np {
namespace net {

class SocketInterface
{
public:
    SocketInterface() = delete;
    SocketInterface(const SocketInterface&) = delete;
    SocketInterface& operator=(const SocketInterface&) = delete;
    virtual ~SocketInterface();

    virtual void listen(int iBacklog) final;
    virtual void close() final;

    virtual ssize_t read(char* oBuffer, size_t iLen) final;
    virtual ssize_t write(const char* iBuffer, size_t iLen) final;

    virtual int getFd() const final;
    virtual SocketType getType() const final;

protected:
    explicit SocketInterface(SocketType iType, int iFileDescriptor);
    explicit SocketInterface(SocketType iType);

    int fd_;
    bool opened_;
    bool closed_;

private:
    SocketType type_;
};

} // namespace net
} // namespace np

#endif /* __SOCKETINTERFACE_H__ */
