#include <string>
#include <iostream>

#include <unistd.h>
#include <sys/socket.h>

#include <np/net/Socket.h>

namespace {

} // namespace

namespace np {
namespace net {

Socket::Socket(int iFamily, int iType)
{
    fd_ = socket(iFamily, iType, 0);
}

void Socket::connect(const std::string& iAddress,
                     const std::string& iPort)
{
}

void Socket::bind(const std::string& iAddress,
                  const std::string& iPort)
{
}

void Socket::listen(int iBacklog)
{
}

Socket Socket::accept()
{
}

void Socket::close()
{
    if(::close(fd_) == -1)
    {
        std::cout << "ERROR: On socket [fd=" << fd_ << "] closure." << std::endl;
    }
}

} // namespace net
} // namespace np
