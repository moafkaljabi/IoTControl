/*

2025

TCP Server 

Responsible for implementing the methods in the socket.h API

- Listens for incoming client connections from devices.
- Spawns a new ClientHandler for each new connection.
- Forwards MQTT publisher to each handler.


*/

#include "TCPServer.h"

TCPServer::TCPServer(int port)
    : port(port), running(false), serverSocket(-1)
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        throw std::runtime_error("Failed to create server socket!");
    }

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);
    sockAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) < 0)
    {
        throw std::runtime_error("Failed to bind server socket!");
    }
}



TCPServer::~TCPServer() 
{
    closeServer();
}



void TCPServer::start()
{
    if (listen(serverSocket, 10) < 0)
    {
        throw std::runtime_error("Failed to listen on server socket!");
    }
    
    running = true;
    std::cout << "Server is listening on port " << port << " ..." << std::endl;

    acceptClients();
}

void TCPServer::stop()
{
    running = false;
    closeServer();
}



void TCPServer::acceptClients()
{
    while (running)
    {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        
        int clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddr, &clientAddrLen);

        if (clientSocket < 0)
        {
            std::cerr << "Failed to accept connection\n"; 
            continue;
        }

        std::cout << "New client connected: " << clientSocket << std::endl;
        clientSockets.push_back(clientSocket);


        auto handler = std::make_unique<ClientHandler>(clientSocket, commandProcessor);
        clientThreads.emplace_back(&ClientHandler::handleClient, handler.get());
        clientHandlers.push_back(st::move(handler));
    }
}




void TCPServer::closeServer()
{
    for (int clientSocket : clientSockets)
    {
        close(clientSocket);
    }
    clientSockets.clear();

    for (std::thread& t : clientThreads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    if (serverSocket >= 0)
    {
        close(serverSocket);
        serverSocket = -1;
    }
}

