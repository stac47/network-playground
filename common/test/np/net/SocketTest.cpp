#include <iostream>
#include <gtest/gtest.h>

#include <np/net/Socket.h>
#include <np/net/SocketFamily.h>
#include <np/net/SocketType.h>
#include <np/net/NetworkException.h>
#include <np/net/Address.h>

using np::net::SocketPtr;
using np::net::Socket;
using np::net::SocketFamily;
using np::net::SocketType;
using np::net::NetworkException;
using np::net::AddressIPv4;

TEST(SocketTest, Creation) {
    SocketPtr socket = Socket::Create(SocketFamily::kIPv4, SocketType::kTCP);
    EXPECT_TRUE(socket != nullptr);
    EXPECT_TRUE(socket->getFd() != -1);
}

TEST(SocketTest, ErrorBindingSamePort)
{
    SocketPtr socket = Socket::Create(SocketFamily::kIPv4, SocketType::kTCP);
    auto address = std::make_shared<AddressIPv4>("127.0.0.1", 8080);
    socket->bind(address);
    try
    {
        socket->bind(address);
        FAIL();
    }
    catch (const NetworkException& e)
    {
        EXPECT_TRUE(e.isSystemError());
        EXPECT_EQ(22, e.getErrno());
        EXPECT_STREQ("Invalid argument", e.what());
    }
    /* EXPECT_THROW(socket->bind("127.0.0.1", 8080), NetworkException); */
}

