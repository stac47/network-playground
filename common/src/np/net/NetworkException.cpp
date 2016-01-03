#include <string>
#include <cstring>
#include <exception>

#include <np/net/NetworkException.h>

namespace np {
namespace net {

NetworkException::NetworkException(const std::string& iWhat)
  : message_(iWhat),
    errno_(-1)
{}

NetworkException::NetworkException(int iErrno)
  : errno_(iErrno)
{
    message_ = std::strerror(iErrno);
}

NetworkException::~NetworkException()
{}

const char* NetworkException::what() const noexcept
{
    return message_.c_str();
}

bool NetworkException::isSystemError() const
{
    return errno_ > 0;
}

int NetworkException::getErrno() const
{
    return errno_;
}

} // namespace net
} // namespace np
