#include "../../include/Mqtt/MQTTPublisher.h"
#include <iostream>

MQTTPublisher::MQTTPublisher(
    const std::string& address,
    const std::string& clientId,
    const std::string& defaultTopic
)
    : topic(defaultTopic),
      client(address, clientId),
      connOpts()
{
    connOpts.set_clean_session(true);
    connect();
}

void MQTTPublisher::connect()
{
    try {
        client.connect(connOpts)->wait();
        std::cout << "[MQTT] Connected to broker\n";
    }
    catch (const mqtt::exception& e) {
        std::cerr << "[MQTT] Connection failed: " << e.what() << std::endl;
    }
}

void MQTTPublisher::publish(const std::string& topic, const std::string& payload)
{
    try {
        client.publish(topic, payload.c_str(), payload.length(), 1, false);
        std::cout << "[MQTT] Published to '" << topic << "': " << payload << std::endl;
    }
    catch (const mqtt::exception& e) {
        std::cerr << "[MQTT] Publish failed: " << e.what() << " — attempting reconnect...\n";
        connect();
    }
}

void MQTTPublisher::publishDefault(const std::string& payload)
{
    publish(topic, payload);
}

MQTTPublisher::~MQTTPublisher()
{
    try {
        if (client.is_connected())
            client.disconnect()->wait();
        std::cout << "[MQTT] Disconnected cleanly\n";
    }
    catch (const mqtt::exception& e) {
        std::cerr << "[MQTT] Disconnect failed: " << e.what() << std::endl;
    }
}
