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

TCPServer::TCPServer(int port) : port(port), serverSocket(-1) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        throw std::runtime_error("Failed to create server socket!");
    }

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);
    sockAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) < 0) {
        throw std::runtime_error("Failed to bind server socket!");
    }
}

TCPServer::~TCPServer() {
    closeServer();
}

void TCPServer::start() {
    if (listen(serverSocket, 10) < 0) {
        throw std::runtime_error("Failed to listen on server socket!");
    }

    std::cout << "Server is listening on port " << port << " ..." << std::endl;

    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "Failed to accept connection!" << std::endl;
            continue;
        }

        std::cout << "New client connected: " << clientSocket << std::endl;
        clientSockets.push_back(clientSocket);
        clientThreads.emplace_back(&TCPServer::handleClient, this, clientSocket);
    }
}

void TCPServer::handleClient(int clientSocket) {
    char buffer[2048] = {0};

    while (true) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived < 0) {
            std::cerr << "Error receiving data from client socket: " << strerror(errno) << std::endl;
            break;
        } else if (bytesReceived == 0) {
            std::cout << "Client disconnected: " << clientSocket << std::endl;
            break;
        }

        std::cout << "Message from client (" << clientSocket << "): " << buffer << std::endl;

        ssize_t bytesSent = send(clientSocket, "Message received", strlen("Message received"), 0);
        if (bytesSent < 0) {
            std::cerr << "Error sending data to client: " << strerror(errno) << std::endl;
        } else {
            std::cout << "Sent message: \"Message received\" (Bytes: " << bytesSent << ")" << std::endl;
        }
    }

    close(clientSocket);
}

void TCPServer::closeServer() {
    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }
    clientSockets.clear();

    for (std::thread& t : clientThreads) {
        if (t.joinable()) {
            t.join();
        }
    }

    if (serverSocket >= 0) {
        close(serverSocket);
    }
}



/*


for error handling: 
Check the return value of recv(). If recv() returns 0, it indicates that the client has closed the connection.
Log whether the disconnection was intentional (e.g., recv() returning 0) or due to an error (e.g., recv() returning -1).


Scaling Beyond Threads

Threads are suitable for a moderate number of clients. For thousands of connections, use asynchronous models (e.g., epoll or select) or frameworks like asio.


*/




