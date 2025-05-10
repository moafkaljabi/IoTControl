#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <rapidjson/document.h>

#include "JSONProcessor.h"
#include "CommandProcessor.h"



class ClientHandler 
{
public:
    ClientHandler(int socket, CommandProcessor& commandProcessor);
    void handleClient();  


private:
    int clientSocket;
    CommandProcessor& commandProcessor;
    JSONProcessor jsonProcessor;

};
