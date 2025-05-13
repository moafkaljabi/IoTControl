// Mqtt/MQTTClient.h

#pragma once
#include <string>
#include <mqtt/async_client.h>

class MyMQTTClient {
public:
    MQTTClient(const std::string& brokerURI, const std::string& clientId);
    bool connect();
    void publish(const std::string& topic, const std::string& payload);
    void disconnect();

private:
    mqtt::async_client client;
};
