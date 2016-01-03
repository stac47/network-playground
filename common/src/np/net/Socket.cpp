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
#include <np/net/AddressFactory.h>
#include <np/net/SocketFamily.h>
#include <np/net/SocketType.h>

#include <np/net/Socket.h>

namespace np {
namespace net {

SocketPtr Socket::Create(SocketFamily iFamily,
                         SocketType iType)
{
    return np::tools::make_shared_from_protected_ctor<Socket>(iFamily, iType);
}

Socket::Socket(int iFileDescriptor)
  : fd_(iFileDescriptor),
    opened_(true),
    closed_(false)
{}

Socket::Socket(SocketFamily iFamily, SocketType iType)
  : fd_(-1),
    family_(iFamily),
    type_(iType),
    closed_(false)
{
    fd_ = socket(static_cast<int>(iFamily), static_cast<int>(iType), 0);
    if (fd_ == -1)
    {
        throw NetworkException(errno);
    }
    else
    {
        opened_ = true;
    }
}

Socket::~Socket()
{
    close();
}

void Socket::connect(const std::string& iAddr, uint16_t iPort)
{
    AddressPtr address = AddressFactory::CreateAddress(family_, iAddr, iPort);
    connect(address);
}

void Socket::connect(const AddressPtr& iAddr)
{
    int s = ::connect(fd_, iAddr->sockaddr(), iAddr->getLength());
    if (s == 0)
    {
        BOOST_LOG_TRIVIAL(info) << "Socket [fd=" << fd_ << "] connected to "
                                << iAddr->toString();
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "Socket [fd=" << fd_ << "] "
                                 << "failed to connect to "
                                 << iAddr->toString();
        throw NetworkException(errno);
    }
}

void Socket::bind(const std::string& iAddr, uint16_t iPort)
{
    AddressPtr address = AddressFactory::CreateAddress(family_, iAddr, iPort);
    bind(address);
}

void Socket::bind(const AddressPtr& iAddr)
{
    int s = ::bind(fd_, iAddr->sockaddr(), iAddr->getLength());
    if (s == 0)
    {
        BOOST_LOG_TRIVIAL(info) << "Socket [fd=" << fd_ << "] bound to "
                                << iAddr->toString();
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "Socket [fd=" << fd_ << "] "
                                 << "failed to bind to "
                                 << iAddr->toString();
        throw NetworkException(errno);
    }
}

void Socket::listen(int iBacklog)
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

SocketPtr Socket::accept()
{
    SocketPtr clientSocketPtr = nullptr;
    int clientSocketFd = 0;
    AddressPtr clientAddress = AddressFactory::CreateEmpty(family_);
    socklen_t len = clientAddress->getLength();
    if ((clientSocketFd = ::accept(fd_, clientAddress->sockaddr(), &len)) == -1)
    {
        BOOST_LOG_TRIVIAL(error) << "Socket [fd=" << fd_ << "] "
                                 << "failed to accept a connection";
        throw NetworkException(errno);
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "Socket [fd=" << fd_ << "] "
                                << "accepted connection from remote client "
                                << "[" << clientAddress->toString() << "]";
        clientSocketPtr = np::tools::make_shared_from_protected_ctor<Socket>(clientSocketFd);
        clientSocketPtr->family_ = clientAddress->getFamily();
        clientSocketPtr->type_ = type_;
    }
    return clientSocketPtr;
}

void Socket::close()
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

ssize_t Socket::read(char* oBuffer, size_t iLen)
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

ssize_t Socket::write(const char* iBuffer, size_t iLen)
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

int Socket::getFd() const
{
    return fd_;
}

} // namespace net
} // namespace np
