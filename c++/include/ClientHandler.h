#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <cstring>
#include <sys/socket.h>
#include <rapidjson/document.h>

#include "IClientDataProcessor.h"



class ClientHandler 
{
public:
    ClientHandler(int socket, std::unique_ptr<IClientDataProcessor> processor);
    void handleClient();  


private:
    int clientSocket;
    std::unique_ptr<IClientDataProcessor> processor;

};
