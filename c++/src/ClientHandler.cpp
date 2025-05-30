/*

2025



- Handles a single client's socket lifecycle.
- Responsibele for: 
    - Reading raw JSON.
    - Passing it to JSONReceiver.
    - Sending JSON using JSONSender.


- Modular: should not depend directly on TCPServer.


*/



#include "ClientHandler.h"
#include "MQTTPublisher.h"

using namespace rapidjson;

ClientHandler::ClientHandler(int socket, CommandProcessor& commandProcessor, MQTTPublisher* mqttPublisher) 
    : clientSocket(socket), commandProcessor(commandProcessor), mqttPublisher(mqttPublisher){}


void ClientHandler::handleClient()
{
    char buffer[4096];

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesReceived <= 0)
        {
            std::cerr << "Client disconnected\n";
            break;
        }

        std::string receivedData(buffer, bytesReceived);
        
        Document document;
        document.Parse(receivedData.c_str());

        if (document.HasParseError())
        {
            std::cerr << "Failed to parse incoming JSON \n";
            continue;
        }

        std::string response = commandProcessor.processCommand(document);

        // To send MQTT
        if (mqttPublisher)
        {
            mqttPublisher->publish("device/status", response);
        }
        
        
        if (send(clientSocket, response.c_str(), response.size(), 0) == -1)
        {
            std::cerr << "Failed to send response to the client \n";
        }
    }

    close(clientSocket);
}