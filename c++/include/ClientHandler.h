#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <boost/asio.hpp>
#include "json/JSONSender.h"  // Include correct path for JSONSender

class ClientHandler 
{

public:
    ClientHandler(std::shared_ptr<boost::asio::ip::tcp::socket> socket); 
    
    void handleClient();  

private:
    
    std::shared_ptr<boost::asio::ip::tcp::socket> clientSocket;

    std::shared_ptr<std::vector<char>> buffer;

    JSONSender jsonSender;  // JSONSender instance for sending responses

    
};
