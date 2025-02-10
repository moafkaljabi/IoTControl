#include <iostream>
#include <cstring> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


int main()
{

    const char* serverAddress = "127.0.0.1";
    int serverPort = 8080;

    int sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFD < 0)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }
    
    // Server address struct
    sockaddr_in serverAddr;
    serverAddr.sin_addr.s_addr = inet_addr(serverAddress);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);

    if (connect(sockFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0 ) 
    {
        std::cerr << "Error from mockClient connect() " << std::endl;
        close(sockFD);
        return 1;
    }
    
    while (true)
    {
    
        rapidjson::Document data;

        data.SetObject();

        rapidjson::Value accelX(10);
        rapidjson::Value accelY(20);
        rapidjson::Value accelZ(30);

        data.AddMember("accelX", accelX, data.GetAllocator());
        data.AddMember("accelY", accelY, data.GetAllocator());
        data.AddMember("accelZ", accelZ, data.GetAllocator());

        // Serializing to JSON 
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        data.Accept(writer);
        std::string jsonData = buffer.GetString();

        jsonData += "\n";

        // Send to server
        send(sockFD, jsonData.c_str(), jsonData.size(),0);
        std::cout << "Sent JSON:" << jsonData << std::endl;
        // Close the socket
        // close(sockFD);





        char recvBuffer[1024] = {0};  

        ssize_t bytesReceived = recv(sockFD, recvBuffer, sizeof(recvBuffer) - 1, 0);
        if (bytesReceived > 0)
        {
            recvBuffer[bytesReceived] = '\0';
            std::cout << "Received from server: " << recvBuffer << std::endl;
        }
        else if (bytesReceived == 0)
        {
            std::cout << "Server closed the connection." << std::endl;
            break;
        }
        else
        {
            std::cerr << "Error receiving data from server" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}