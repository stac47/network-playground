#include <string>
#include <iostream>
#include <cstring>
#include <cerrno>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>

#include <np/tools/make_shared_from_protected_ctor.h>
#include <np/net/NetworkException.h>
#include <np/net/Address.h>
#include <np/net/SocketType.h>

#include <np/net/Socket.h>

namespace np {
namespace net {

template<typename A>
std::shared_ptr<Socket<A>> Socket<A>::Create(SocketType iType)
{
    /* return np::tools::make_shared_from_protected_ctor<Socket>(iType); */
    return std::shared_ptr<Socket<A>>(new Socket<A>(iType));
}

template<typename A>
Socket<A>::Socket(SocketType iType, int iFileDescriptor)
  : SocketInterface(iType, iFileDescriptor)
{}

template<typename A>
Socket<A>::~Socket() {}

template<typename A>
Socket<A>::Socket(SocketType iType)
  : SocketInterface(iType)
{
    closed_ = false;
    fd_ = socket(A::GetFamily(), static_cast<int>(iType), 0);
    if (fd_ == -1)
    {
        throw NetworkException(errno);
    }
    else
    {
        opened_ = true;
    }
}

template<typename A>
void Socket<A>::connect(const A& iAddr)
{
    int s = ::connect(fd_, iAddr.sockaddr(), iAddr.getLength());
    if (s == 0)
    {
        BOOST_LOG_TRIVIAL(info) << "Socket [fd=" << fd_ << "] connected to "
                                << iAddr.toString();
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "Socket [fd=" << fd_ << "] "
                                 << "failed to connect to "
                                 << iAddr.toString();
        throw NetworkException(errno);
    }
}

template<typename A>
void Socket<A>::bind(const A& iAddr)
{
    int s = ::bind(fd_, iAddr.sockaddr(), iAddr.getLength());
    if (s == 0)
    {
        BOOST_LOG_TRIVIAL(info) << "Socket [fd=" << fd_ << "] bound to "
                                << iAddr.toString();
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "Socket [fd=" << fd_ << "] "
                                 << "failed to bind to "
                                 << getLocalAddress()->toString();
        throw NetworkException(errno);
    }
}

template<typename A>
std::shared_ptr<Socket<A>> Socket<A>::accept()
{
    std::shared_ptr<Socket<A>> clientSocketPtr = nullptr;
    int clientSocketFd = 0;
    A clientAddress;
    socklen_t len = clientAddress.getLength();
    if ((clientSocketFd = ::accept(fd_, clientAddress.sockaddr(), &len)) == -1)
    {
        BOOST_LOG_TRIVIAL(error) << "Socket [fd=" << fd_ << "] "
                                 << "failed to accept a connection";
        throw NetworkException(errno);
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "Socket [fd=" << fd_ << "] "
                                << "accepted connection from remote client "
                                << "[" << clientAddress.toString() << "]";
        clientSocketPtr = std::shared_ptr<Socket<A>>(new Socket<A>(getType(), clientSocketFd));
    }
    return clientSocketPtr;
}

template<typename A>
std::shared_ptr<A> Socket<A>::getLocalAddress() const
{
    auto ret = std::make_shared<A>();
    socklen_t len = ret->getLength();
    if (::getsockname(fd_, ret->sockaddr(), &len) == -1)
    {
        BOOST_LOG_TRIVIAL(error) << "Unable to get local address from "
                                 << "socket [fd=" << fd_ << "] ";
        ret = nullptr;
    }
    return ret;
}

template<typename A>
std::shared_ptr<A> Socket<A>::getRemoteAddress() const
{
    auto ret = std::make_shared<A>();
    socklen_t len = ret->getLength();
    if (::getpeername(fd_, ret->sockaddr(), &len) == -1)
    {
        BOOST_LOG_TRIVIAL(error) << "Unable to get remote address from "
                                 << "socket [fd=" << fd_ << "] ";
        ret = nullptr;
    }
    return ret;
}

} // namespace net
} // namespace np
