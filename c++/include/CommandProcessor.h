/*

2025

This class is to process commands after receiving them from the JSONReceiver class.



[TCPServer]
     ↓
[ClientHandler] ← receives string over socket
     ↓
[JSONReceiver] ← parses it into JSON object
     ↓
[CommandProcessor] ← interprets & runs actions based on command
     ↓
[JSONSender] ← sends result/status response back



*/


#pragma once 

#include <iostream>
#include <string>
#include "rapidjson/document.h"



class MQTTPublisher;

class CommandProcessor {

public:
    
    CommandProcessor(MQTTPublisher& mqttPublisher);
//     std::string processCommand(const rapidjson::Document& jsonDoc);
       virtual void processCommand(const rapidjson::Document& jsonDoc);


private:

    enum class CommandType{
        TURN_LED,
        GET_STATUS,
        DISCONNECT,
        UNKNOWN
    };

    CommandType getCommandType(const std::string& command);

    // Command handlers
    std::string handlTurnLED();
    std::string handleStatusRequest();

    std::string handleDisconnect();
    
    MQTTPublisher& mqttPublisher;

};
