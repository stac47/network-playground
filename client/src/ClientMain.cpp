#include <string>

#include <boost/log/trivial.hpp>

#include <np/net/Address.h>
#include <np/net/Socket.h>

int main(int argc, const char* argv[])
{

    using namespace np::net;
    BOOST_LOG_TRIVIAL(info) << "Client starting...";
    SocketPtr socket = Socket::Create(SocketFamily::kIPv4, SocketType::kTCP);
    socket->connect(std::make_shared<AddressIPv4>("127.0.0.1", 4747));
    char buffer[5];
    ssize_t l = socket->read(buffer, 5);
    BOOST_LOG_TRIVIAL(info) << "Reply [size=" << l << "]: " << std::string(buffer, l);
    socket->write("12345", 5);
    return 0;;
}
