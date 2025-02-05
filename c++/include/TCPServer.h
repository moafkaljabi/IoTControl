#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

#include "ClientHandler.h"

class TCPServer 
{
public:
    TCPServer(int port);
    ~TCPServer();
    void start();

private:
    int serverSocket;
    int port;
    sockaddr_in sockAddr;
    
    std::vector<int> clientSockets;  // Tracks connected client sockets
    std::vector<std::thread> clientThreads;  // Manages client handling threads
    std::vector<std::unique_ptr<ClientHandler>> clientHandlers;  // Manages ClientHandler instances


  
    void closeServer();
};
