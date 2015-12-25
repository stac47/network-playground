#include <string>
#include <iostream>

#include <unistd.h>
#include <sys/socket.h>

#include <np/tools/make_shared_from_protected_ctor.h>
#include <np/net/NetworkException.h>
#include <np/net/Socket.h>

namespace {

} // namespace

namespace np {
namespace net {

SocketPtr Socket::Create(int iFamily, int iType)
{
    return np::tools::make_shared_from_protected_ctor<Socket>(iFamily, iType);
}

Socket::Socket(int iFamily, int iType)
  : closed_(false)
{
    fd_ = socket(iFamily, iType, 0);
    if (fd_ == -1)
    {
        throw NetworkException();
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

SocketPtr Socket::accept()
{
    return nullptr;
}

void Socket::close()
{
    if (!opened_ || closed_)
    {
        // TODO output a log
        return;
    }
    if(::close(fd_) == -1)
    {
        std::cout << "ERROR: On socket [fd=" << fd_ << "] closure." << std::endl;
    }
    closed_ = true;
}

} // namespace net
} // namespace np
