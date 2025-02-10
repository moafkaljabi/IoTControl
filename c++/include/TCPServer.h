#pragma once 


#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <optional> // to delay initializtions
#include <boost/asio.hpp>

#include "ClientHandler.h"


class TCPServer {

public:
    
    TCPServer(int port);
    void start();
    void stop();

private:

    void acceptConnection();
    boost::asio::io_context ioc;
    boost::asio::ip::tcp::acceptor acceptor;
    std::vector<std::thread> threadPool;
    std::optional<ClientHandler>clientHandler;
};