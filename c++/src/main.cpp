#include "main.h"

#include "TCPServer.h"
#include "MQTTPublisher.h"

int main()
{
    try 
    {
        const std::string mqttAddress = "tcp://localhost:1883";
        const std::string mqttClientId = "cpp_server";
        const std::string defaultTopic = "device/status";

        MQTTPublisher mqttPublisher(mqttAddress, mqttClientId, defaultTopic);
        //TCPServer server(8080, &mqttPublisher);
        TCPServer server(8080);

        server.start();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "[Main] Server error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
