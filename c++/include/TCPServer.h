#pragma once 


#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include <boost/asio.hpp>


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
};