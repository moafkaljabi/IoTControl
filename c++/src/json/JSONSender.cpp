#include "JSONSender.h"


// Constructor to initialize the client socket 
JSONSender::JSONSender(
    std::shared_ptr<boost::asio::ip::tcp::socket> clientSocket,
    const std::string& clientAddress,
    int clientPort
)
:   clientSocket(clientSocket),
    clientAddress (clientAddress),
    clientPort (clientPort)
{}


void JSONSender::sendJSON()
{

    if (!clientSocket || !clientSocket->is_open()) 
    {
        std::cerr << "Error from sendJSON: Invalid or closed socket" << std::endl;
        return;
    }


    // Create JSON Object
    rapidjson::Document JsonDocument;
    JsonDocument.SetObject();
    rapidjson::Document::AllocatorType& allocator = JsonDocument.GetAllocator();

    // Add data to the JSON object
    JsonDocument.AddMember("status", rapidjson::Value("Success", allocator), allocator);
    JsonDocument.AddMember("message", rapidjson::Value("Hello from the C++ server!", allocator), allocator);


    // Get the client ip and port
    JsonDocument.AddMember("client_ip", rapidjson::Value(clientAddress.c_str(),allocator), allocator);
    JsonDocument.AddMember("client_port",clientPort,allocator);


    // Serialize JSON to string .... stringBuffwer, writer, accept
    rapidjson::StringBuffer stringBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
    JsonDocument.Accept(writer);

    // Get JSON
    jsonResponse = stringBuffer.GetString();
    jsonResponse += "\n"; // Delimeier


    if (!clientSocket || !clientSocket->is_open())
    {
    std::cerr << "Socket closed before writing JSON!" << std::endl;
    return;
    }

    // Send
    boost::asio::async_write(*clientSocket, boost::asio::buffer(jsonResponse),
    [this] (const boost::system::error_code &ec, size_t bytesTransferred)
    {
        if(!ec)
        {
            std::cout << "Sent JSON (" << bytesTransferred << "bytes)" << std::endl; 
        }
        else 
        {
            std::cerr << "Error from JSONSender: " << ec.message() << std::endl;
        }
    }
    );


}





