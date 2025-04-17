#include "../../include/Mqtt/MqqtClient.h"


// mqtt/MQTTClient.cpp

#include "MQTTClient.h"
#include <iostream>

MQTTClient::MQTTClient(const std::string& brokerURI, const std::string& clientId)
    : client(brokerURI, clientId) {}

bool MQTTClient::connect() {
    try {
        client.connect()->wait();
        std::cout << "Connected to MQTT broker." << std::endl;
        return true;
    } catch (const mqtt::exception& e) {
        std::cerr << "MQTT connect failed: " << e.what() << std::endl;
        return false;
    }
}

void MQTTClient::publish(const std::string& topic, const std::string& payload) {
    try {
        client.publish(topic, payload.c_str(), payload.size(), 1, false);
        std::cout << "Published to topic: " << topic << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "Publish failed: " << e.what() << std::endl;
    }
}

void MQTTClient::disconnect() {
    try {
        client.disconnect()->wait();
        std::cout << "Disconnected from MQTT broker." << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "Disconnect failed: " << e.what() << std::endl;
    }
}
