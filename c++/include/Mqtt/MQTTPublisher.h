/*

mqtt/MQTTPublisher.h

*/



#pragma once


#include <string>
#include <memory>
#include <mqtt/async_client.h>

class MQTTPublisher {

public:
    
    MQTTPublisher
    (
        const std::string& address,
        const std::string& clientId,
        const std::string& topic
    );
    
    void publish(const std::string& topic , const std::string& payload);
    void publishDefault(const std::string& payload);


    ~MQTTPublisher();

private:
    
    std::string topic;
    mqtt::async_client client;
    mqtt::connect_options connOpts;

    void connect();
};
