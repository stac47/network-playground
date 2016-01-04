#include <string>

#include <boost/log/trivial.hpp>

#include <np/net/Socket.h>
#include <np/net/AddressIPv4.h>

int main(int argc, const char* argv[])
{
    using namespace np::net;
    BOOST_LOG_TRIVIAL(info) << "Server starting...";
    auto socket = Socket<AddressIPv4>::Create(SocketType::kTCP);
    AddressIPv4 address("127.0.0.1", 4747);
    socket->bind(address);
    socket->listen(5);
    auto clientSocket = socket->accept();
    std::string s = "Hello World\n";
    clientSocket->write(s.data(), s.size());
    char buffer[5];
    ssize_t l = clientSocket->read(buffer, 5);
    std::string reply(buffer, l);
    BOOST_LOG_TRIVIAL(info) << "Reply [size=" << l << "]: " << reply;
    return 0;
}
