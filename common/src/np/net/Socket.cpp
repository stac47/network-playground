#include <string>
#include <iostream>
#include <cstring>
#include <cerrno>

#include <unistd.h>
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
    return np::tools::make_shared_from_protected_ctor<Socket>(iType);
}

template<typename A>
Socket<A>::Socket(int iFileDescriptor)
  : fd_(iFileDescriptor),
    opened_(true),
    closed_(false)
{}

template<typename A>
Socket<A>::~Socket()
{
    close();
}

template<typename A>
void Socket<A>::listen(int iBacklog)
{
    if (::listen(fd_, iBacklog) == -1)
    {
        BOOST_LOG_TRIVIAL(error) << "Socket [fd=" << fd_ << "] "
                                 << "failed to become a passive listening socket";
        throw NetworkException(errno);
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "Socket [fd=" << fd_ << "] "
                                 << "is listening. Backlog value = " << iBacklog;
    }
}

template<typename A>
void Socket<A>::close()
{
    BOOST_LOG_TRIVIAL(info) << "Closing the socket [fd=" << fd_ << "]";
    if (!opened_ || closed_)
    {
        // fd_ still has the initial value. Once fd_ is set, it cannot be
        // modified during the Socket lifetime
        BOOST_LOG_TRIVIAL(warning) << "Trying to close the socket [fd=" << fd_ << "] a second time";
        return;
    }
    if(::close(fd_) == -1)
    {
        BOOST_LOG_TRIVIAL(error) << "Problem when closing the socket [fd=" << fd_ << "]";
    }
    closed_ = true;
    BOOST_LOG_TRIVIAL(info) << "Socket [fd=" << fd_ << "] closed";
}

template<typename A>
int Socket<A>::getFd() const
{
    return fd_;
}

template<typename A>
Socket<A>::Socket(SocketType iType)
  : fd_(-1),
    type_(iType),
    closed_(false)
{
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
                                 << iAddr.toString();
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
        clientSocketPtr = np::tools::make_shared_from_protected_ctor<Socket<A>>(clientSocketFd);
        clientSocketPtr->type_ = type_;
    }
    return clientSocketPtr;
}

template<typename A>
ssize_t Socket<A>::read(char* oBuffer, size_t iLen)
{
    size_t nleft = iLen;

    while (nleft > 0)
    {
        ssize_t nread = 0;
        if ((nread = ::read(fd_, oBuffer, nleft)) < 0)
        {
            if (errno == EINTR)
            {
                nread = 0;
            }
            else
            {
                return -1;
            }
        }
        else if (nread == 0)
        {
            break;
        }
        nleft -= nread;
        oBuffer += nread;
    }
    return (iLen - nleft);
}

template<typename A>
ssize_t Socket<A>::write(const char* iBuffer, size_t iLen)
{
    ssize_t nleft = iLen;
    const char* buffer = iBuffer;
    while (nleft > 0)
    {
        ssize_t nwritten = 0;
        if ((nwritten = ::write(fd_, buffer, nleft)) <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
            {
                nwritten = 0;
            }
            else
            {
                return -1;
            }
        }
        nleft -= nwritten;
        buffer += nwritten;
    }
    return iLen;
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
