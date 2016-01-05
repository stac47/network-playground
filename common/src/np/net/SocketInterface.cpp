#include <unistd.h>

#include <boost/log/trivial.hpp>

#include <np/net/NetworkException.h>
#include <np/net/SocketInterface.h>

namespace np {
namespace net {

SocketInterface::SocketInterface(SocketType iType, int iFileDescriptor)
  : fd_(iFileDescriptor),
    opened_(true),
    closed_(false),
    type_(iType)
{}

SocketInterface::SocketInterface(SocketType iType)
  : type_(iType)
{}

SocketInterface::~SocketInterface()
{
    close();
}

int SocketInterface::getFd() const
{
    return fd_;
}

SocketType SocketInterface::getType() const
{
    return type_;
}

void SocketInterface::listen(int iBacklog)
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

void SocketInterface::close()
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

ssize_t SocketInterface::read(char* oBuffer, size_t iLen)
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

ssize_t SocketInterface::write(const char* iBuffer, size_t iLen)
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


} // namespace net
} // namespace np
