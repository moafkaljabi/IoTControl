#pragma once

#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>

#include "json/JSONSender.h"
#include "Mqtt/MQTTPublisher.h"

class MQTTPublisher;


class ClientHandler 
{
public:
   
    ClientHandler(int socket, std::shared_ptr<MQTTPublisher> mqttPublisher);  // Constructor to initialize jsonSender
    void handleClient();  // Function to handle client communication

private:
    
int clientSocket;
    JSONSender jsonSender;  // JSONSender instance for sending responses

    std::shared_ptr<MQTTPublisher> mqttPublisher;

};
