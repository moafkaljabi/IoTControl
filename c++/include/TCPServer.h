/*

2025

TCP Server 

Responsible for implemnting the methods in the socket.h API


- Listens for incoming client connections from devices.
- Spawns a new ClientHandler for each new connection.

should be modular, so it can be replaced/work along a Http server, WebSockets and etc.


*/



#pragma once


#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>

#include "ClientHandler.h"
#include "CommandProcessor.h"



class TCPServer 
{
public:
    TCPServer(int port);
    ~TCPServer();

    void start();
    void stop();    

    
private:
    int serverSocket;
    int port;
    bool running;
    
    sockaddr_in sockAddr;

    CommandProcessor commandProcessor;

    std::vector<int>clientSockets;
    std::vector<std::thread> clientThreads;  // Manages client handling threads
    std::vector<std::unique_ptr<ClientHandler>> clientHandlers;  // Manages ClientHandler instances
    

private:
    void acceptClients();
    void closeServer();
    
};
