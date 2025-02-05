/*

1- Create the socket.

2- Define our address.

3- Bind

4- Listen

5- Accept

6- Recv

7- Close

- concurrency

gLock - 


- Error Handling  - Protocol design - Security  - Data Handling

*/

#include "TCPServer.h"


TCPServer::TCPServer(int port) : port(port), serverSocket(-1)
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

    std::cout << "Server is listening on port " << port << " ..." << std::endl;

    while (true)
    {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0)
        {
            std::cerr << "Failed to accept connection!" << std::endl;
            continue;
        }

        std::cout << "New client connected: " << clientSocket << std::endl;
        clientSockets.push_back(clientSocket);

        clientHandlers.emplace_back(std::make_unique<ClientHandler>(clientSocket));
        clientThreads.emplace_back(&ClientHandler::handleClient, clientHandlers.back().get());

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
        if (t.joinable()) {
            t.join();
        }
    }

    if (serverSocket >= 0)
    {
        close(serverSocket);
    }
}



/*


Scaling Beyond Threads

Threads are suitable for a moderate number of clients. For thousands of connections, use asynchronous models (e.g., epoll or select) or frameworks like asio.


*/




