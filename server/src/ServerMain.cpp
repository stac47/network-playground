#include <string>

#include <sys/socket.h>

#include <np/net/Socket.h>

int main(int argc, const char* argv[])
{
    np::net::SocketPtr socket = np::net::Socket::Create(AF_INET, SOCK_STREAM);
    socket->close();
    return 0;
}
