/*

2025


- Handles a single client's socket lifecycle.
- Responsibele for: 
    - Reading raw JSON.
    - Passing it to JSONReceiver.
    - Sending JSON using JSONSender.

    - Forwarding to MqttPublisher.

- Modular: should not depend directly on TCPServer.


*/



#include "ClientHandler.h"
#include <cstring>
#include <sys/socket.h>

#include "json/JSONReceiver.h" 
#include "CommandProcessor.h"



ClientHandler::ClientHandler(int socket, MQTTPublisher& mqttPub) 
    : clientSocket(socket), jsonSender(clientSocket), mqttPublisher(mqttPub) 
    {}

void ClientHandler::handleClient()
{
    char buffer[2048] = {0};

    JSONReceiver jsonReceiver;
    CommandProcessor commandProcessor(MQTTPublisher& mqttPublisher); // Pass MQTTPublisher instance

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

        // Parse Json and process it 
        rapidjson::Document doc;
        if (jsonReceiver.parseJSON(jsonData, doc)) 
        {
            std::string response = commandProcessor.processCommand(doc);

            // Check for disconnect command
            if (doc.HasMember("command") && doc["command"].IsString() &&
                std::string(doc["command"].GetString()) == "disconnect") {
                jsonSender.sendResponse("Disconnected. Goodbye!");
                break;
            }

            jsonSender.sendResponse(response);
        } 
        else 
        {
            jsonSender.sendError("Invalid JSON format");
        }

    }

    close(clientSocket);
}


