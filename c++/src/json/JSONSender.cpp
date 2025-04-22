/*

2025


- Builds and sends outgoing JSON.

- Uses RapidJSON.

- Sends through a socket passed at construction.

*/





#include "JSONSender.h"


// Constructor to initialize the client socket 
JSONSender::JSONSender(int clientSocket) : clientSocket(clientSocket) {}


void JSONSender::sendHello()
{
    rapidjson::Document document;

    document.SetObject();

    auto& allocator = document.GetAllocator();

    document.AddMember("status", "success", allocator);
    document.AddMember("message", "Welcome to the C++ server", allocator);

    sendJSON(document);
}



void JSONSender::sendResponse(const std::string& response)
{
    rapidjson::Document document;
    document.SetObject();

    auto& allocator = document.GetAllocator();

    document.AddMember("status", "success", allocator);
    document.AddMember("message",rapidjson::Value(response.c_str(),allocator), allocator);

    sendJSON(document);
}


void JSONSender::sendError(const std::string& error)
{
    rapidjson::Document document;
    document.SetObject();

    auto& allocator = document.GetAllocator();

    document.AddMember("status", "Error", allocator);
    document.AddMember("message", rapidjson::Value(error.c_str(), allocator), allocator);

    sendJSON(document);
}


void JSONSender::sendJSON(const rapidjson::Document& document)
{
    // Buffer
    rapidjson::StringBuffer buffer;

    // Writer 
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    // Accept 
    document.Accept(writer);

    // String 
    std::string jsonString = buffer.GetString();
    jsonString += "\n";

    
    // BytesSent 
    ssize_t bytesSent = send(clientSocket, jsonString.c_str(), jsonString.length(), 0);

    // Check if successfully sent
    if(bytesSent < 0)
    {
        // Do NOT use "sendError" here cause it uses this "sendJSON" we are in
        std::cerr << "Error sending JSON: " << strerror(errno) << std::endl;
    }
    else
    {
        std::cout << "Sent JSON: " << jsonString << "(Bytes: " << bytesSent << ")" << std::endl;
    }

}