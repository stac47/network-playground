#include <string>

#include <boost/log/trivial.hpp>

#include <np/net/AddressIPv4.h>
#include <np/net/Socket.h>

using np::net::Socket;
using np::net::AddressIPv4;
using np::net::SocketType;

int main(int argc, const char* argv[])
{

    BOOST_LOG_TRIVIAL(info) << "Client starting...";
    auto socket = Socket<AddressIPv4>::Create(SocketType::kTCP);
    AddressIPv4 address("127.0.0.1", 4747);
    socket->connect(address);
    char buffer[5];
    ssize_t l = socket->read(buffer, 5);
    BOOST_LOG_TRIVIAL(info) << "Reply [size=" << l << "]: " << std::string(buffer, l);
    socket->write("12345", 5);
    return 0;;
}
