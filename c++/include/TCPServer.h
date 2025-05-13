#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <unistd.h>
#include <memory>

#include "ClientHandler.h"
#include "CommandProcessor.h"

class TCPServer 
{
public:
    TCPServer(int port, MQTTPublisher* mqttPublisher);
    ~TCPServer();

    void start();
    void stop();    

private:
    int serverSocket;
    int port;
    bool running;

    sockaddr_in sockAddr;

    CommandProcessor commandProcessor;

    MQTTPublisher* mqttPublisher = nullptr;

    std::vector<int> clientSockets;
    std::vector<std::thread> clientThreads;
    std::vector<std::unique_ptr<ClientHandler>> clientHandlers;

    void acceptClients();
    void closeServer();
};
