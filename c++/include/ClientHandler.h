#pragma once

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include "json/JSONSender.h"
//#include <memory>
class ClientHandler : public std::enable_shared_from_this<ClientHandler>
{
public:
    ClientHandler(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void handleClient();  

private:
    std::shared_ptr<boost::asio::ip::tcp::socket> clientSocket;
    std::string clientAddress;  // Declare before jsonSender
    int clientPort;             // Declare before jsonSender
    std::shared_ptr<std::vector<char>> buffer;
    std::shared_ptr<JSONSender> jsonSender;
};
