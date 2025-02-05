#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>

#include "json/JSONSender.h"  // Include correct path for JSONSender

class ClientHandler 
{
public:
    ClientHandler(int socket);  // Constructor to initialize jsonSender
    void handleClient();  // Function to handle client communication

private:
    int clientSocket;
    JSONSender jsonSender;  // JSONSender instance for sending responses
};
