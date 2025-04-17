/*


mqtt/MQTTPublisher.cpp


2025

- Published parsed data to to MQTT.

- Called by ClientHandler to publish messages.

- Should not know about TCP or sockets.

- Sends data to a topic.

- Uses MqttClient to do the actual communication.


*/ 



#include "../../include/Mqtt/MQTTPublisher.h"
#include <iostream>



MQTTPublisher::MQTTPublisher(const std::string& address, const std::string& clientId, const std::string& topic)
    : topic(topic), client(address, clientId), connOpts() 
{
    connOpts.set_clean_session(true);
    try {
        client.connect(connOpts)->wait();
        std::cout << "[MQTT] Connected to broker: " << address << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "[MQTT] Connection failed: " << e.what() << std::endl;
    }
}

void MQTTPublisher::publish(const std::string& payload)
{
    try {
        client.publish(topic, payload.c_str(), payload.length(), 1, false);
        std::cout << "[MQTT] Published to topic '" << topic << "': " << payload << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "[MQTT] Publish failed: " << e.what() << std::endl;
    }
}
