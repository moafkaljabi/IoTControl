#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <string>
#include <iostream>
#include <sys/socket.h> // For `send`

void sendJSON(int clientSocket) {
    // Create a JSON object
    rapidjson::Document jsonDoc;
    jsonDoc.SetObject();
    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();

    // Add some data to the JSON
    jsonDoc.AddMember("status", "success", allocator);
    jsonDoc.AddMember("message", "Hello from the C++ server!", allocator);
    jsonDoc.AddMember("client_id", clientSocket, allocator);

    // Serialize JSON to string
    rapidjson::StringBuffer stringBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
    jsonDoc.Accept(writer);

    // Get the serialized JSON string
    std::string jsonResponse = stringBuffer.GetString();

    // Adding delimiter 
    jsonResponse += "\n";

    // Send the JSON string over the socket
    ssize_t bytesSent = send(clientSocket, jsonResponse.c_str(), jsonResponse.length(), 0);
    if (bytesSent < 0) {
        std::cerr << "Error sending JSON: " << strerror(errno) << std::endl;
    } else {
        std::cout << "Sent JSON: " << jsonResponse << " (Bytes: " << bytesSent << ")" << std::endl;
    }
}
