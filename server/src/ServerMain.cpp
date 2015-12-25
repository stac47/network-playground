#include <string>

#include <sys/socket.h>

#include <np/net/Socket.h>

int main(int argc, const char* argv[])
{
    np::net::Socket socket(AF_INET, SOCK_STREAM);
    socket.close();
    return 0;
}
