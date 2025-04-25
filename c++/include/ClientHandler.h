#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>

#include "json/JSONSender.h"
#include "IClientDataProcessor.h"



class ClientHandler 
{
public:
   
    ClientHandler(int socket, IClientDataProcessor& iClientDataProcessor);
    void handleClient();  

private:
    
int clientSocket;
JSONSender jsonSender;  // JSONSender instance for sending responses

IClientDataProcessor& iClientDataProcessor;

};
