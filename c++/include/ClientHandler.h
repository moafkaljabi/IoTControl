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
   
    ClientHandler(int socket, MQTTPublisher& mqttPublisher );
    void handleClient();  

private:
    
int clientSocket;
JSONSender jsonSender;  // JSONSender instance for sending responses

MQTTPublisher& mqttPublisher;


};
