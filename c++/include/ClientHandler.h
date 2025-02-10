#pragma once

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include "json/JSONSender.h"

// allows the object to safely create a std::shared_ptr to itself. for any async function.
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
