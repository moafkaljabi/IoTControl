#pragma once

#include <string>
#include <mqtt/async_client.h>

class MQTTPublisher {
public:
    MQTTPublisher(
        const std::string& address,
        const std::string& clientId,
        const std::string& defaultTopic
    );

    void publish(const std::string& topic, const std::string& payload);
    void publishDefault(const std::string& payload);

    ~MQTTPublisher();

private:
    std::string topic;
    mqtt::async_client client;
    mqtt::connect_options connOpts;

    void connect();  // Internal retry logic
};
