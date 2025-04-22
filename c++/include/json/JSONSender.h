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


class JSONSender
{
public:
    explicit JSONSender(int clientSocket);

    void sendHello();
    void sendResponse(const std::string& response); // Costum Response
    void sendError(const std::string& error);


private:
    int clientSocket;

private:
    void sendJSON(const rapidjson::Document& document);

};


