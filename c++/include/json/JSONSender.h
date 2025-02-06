/* 



This Class is responsible for serializing data into JSON and sending it.

*/

#pragma once 

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <string>
#include <iostream>
#include <sys/socket.h> // For `send`

#include <boost/asio.hpp>

class JSONSender
{
public:
    explicit JSONSender(std::shared_ptr<boost::asio::ip::tcp::socket> clientSocket);

    void sendJSON();

    std::string jsonResponse;

private:
    std::shared_ptr<boost::asio::ip::tcp::socket> clientSocket;

    std::string clientAddress;
    int clientPort;

};


