#include "ClientHandler.h"
#include "json/JSONReceiver.h" // Include JSONReceiver
#include <cstring>
#include <sys/socket.h>

ClientHandler::ClientHandler(int socket) : clientSocket(socket), jsonSender(clientSocket) {}

void ClientHandler::handleClient()
{
    char buffer[2048] = {0};

    while (true) 
    {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived < 0) {
            std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
            break;
        } else if (bytesReceived == 0) {
            std::cout << "Client disconnected: " << clientSocket << std::endl;
            break;
        }

        buffer[bytesReceived] = '\0'; // Null-terminate the received data
        std::string jsonData(buffer);

        // Log received message
        std::cout << "Message from client (" << clientSocket << "): " << jsonData << std::endl;

        // Call JSONReceiver to parse and pretty-print JSON
        JSONReceiver::parseJSON(jsonData);
        

        // Send a response back to the client
        jsonSender.sendJSON();  
    }

    close(clientSocket);
}
