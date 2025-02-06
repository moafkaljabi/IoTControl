#pragma once

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include "json/JSONSender.h"

class ClientHandler 
{
public:
    ClientHandler(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void handleClient();  

private:
    std::shared_ptr<boost::asio::ip::tcp::socket> clientSocket;
    std::string clientAddress;  // Declare before jsonSender
    int clientPort;             // Declare before jsonSender
    std::shared_ptr<std::vector<char>> buffer;
    JSONSender jsonSender;      // Now correctly placed after clientAddress and clientPort
};
