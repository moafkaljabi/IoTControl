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
#include "IClientDataProcessorFactory.h"

#include "CommandProcessor.h"
#include "CommandProcessorAdapter.h"




class TCPServer 
{
public:
    TCPServer(int port, IClientDataProcessorFactory& iClientDataProcessorFactory);
    ~TCPServer();

    void start();
    void stop();    

    
private:
    int serverSocket;
    int port;
    bool running;
    sockaddr_in sockAddr;
    
    std::vector<int> clientSockets;
    std::vector<std::thread> clientThreads;  // Manages client handling threads
    std::vector<std::unique_ptr<ClientHandler>> clientHandlers;  // Manages ClientHandler instances
    
    IClientDataProcessorFactory iClientDataProcessorFactory;

private:
    void acceptClients();
    void closeServer();
    
};
