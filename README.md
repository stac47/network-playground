# Network Playground

Just a project to play with sockets and C++ 14.

# Dependencies

## boost-log

I generally install the whole boost libraries:

    $ sudo apt-get install libboost-all-dev

To install only the needed one:

    $ sudo apt-get install libboost-log-dev

## gtest (for tests only)

    $ sudo apt-get install libgtest-dev
    $ cd /usr/src/gtest
    $ sudo cmake .
    $ sudo make
    $ sudo cp libgtest* /usr/lib

