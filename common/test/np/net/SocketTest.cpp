#include <gtest/gtest.h>

#include <np/net/Socket.h>
#include <np/net/SocketType.h>
#include <np/net/NetworkException.h>
#include <np/net/Address.h>

using np::net::Socket;
using np::net::SocketType;
using np::net::NetworkException;
using np::net::AddressIPv4;

TEST(SocketTest, Creation) {
    auto socket = Socket<AddressIPv4>::Create(SocketType::kTCP);
    EXPECT_TRUE(socket != nullptr);
    EXPECT_TRUE(socket->getFd() != -1);
}

TEST(SocketTest, ErrorBindingSamePort)
{
    auto socket = Socket<AddressIPv4>::Create(SocketType::kTCP);
    AddressIPv4 address("127.0.0.1", 0);
    socket->bind(address);
    auto localAddress = socket->getLocalAddress();
    EXPECT_EQ(localAddress->getAddress(), "127.0.0.1");
    try
    {
        socket->bind(*localAddress);
        FAIL();
    }
    catch (const NetworkException& e)
    {
        EXPECT_TRUE(e.isSystemError());
        EXPECT_EQ(22, e.getErrno());
        EXPECT_STREQ("Invalid argument", e.what());
    }
}

