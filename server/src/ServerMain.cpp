#include <string>

#include <sys/socket.h>

#include <boost/log/trivial.hpp>

#include <np/net/Socket.h>

int main(int argc, const char* argv[])
{
    using namespace np::net;
    BOOST_LOG_TRIVIAL(info) << "Server starting...";
    SocketPtr socket = Socket::Create(SocketFamily::kIPv4, SocketType::kTCP);
    socket->bind("", "4747");
    socket->listen(5);
    SocketPtr clientSocket = socket->accept();
    std::string s = "Hello World\n";
    clientSocket->write(s.data(), s.size());
    char buffer[5];
    ssize_t l = clientSocket->read(buffer, 5);
    std::string reply(buffer, l);
    BOOST_LOG_TRIVIAL(info) << "Reply [size=" << l << "]: " << reply;
    clientSocket->close();
    socket->close();
    return 0;
}
