#ifndef __NETWORKEXCEPTION_H__
#define __NETWORKEXCEPTION_H__

#include <string>
#include <exception>

namespace np {
namespace net {

class NetworkException : public std::exception
{
public:
    NetworkException(const std::string& iWhat);
    NetworkException(int iErrno);
    ~NetworkException() override;

    const char* what() const noexcept override;

    bool isSystemError() const;
    int getErrno() const;


private:
    std::string message_;
    int errno_;
};

} // namespace net
} // namespace np

#endif /* __NETWORKEXCEPTION_H__ */
