/*

2025




*/



#include "CommandProcessor.h"
#include "MQTTPublisher.h"

CommandProcessor::CommandProcessor(MQTTPublisher& mqttPublisher)
    : mqttPublisher(mqttPublisher) {}

std::string CommandProcessor::processCommand(const rapidjson::Document& jsonDoc)
{
    // Check if the command is proper
    if (!jsonDoc.HasMember("command") || !jsonDoc["command"].IsString())
    {
        return "Invalid commanf format...";
    }

    std::string command = jsonDoc["command"].GetString();
    CommandType commandType = getCommandType(command);

    switch (commandType) {
        case CommandType::TURN_LED:
            return handlTurnLED();
        case CommandType::GET_STATUS:
            return handleStatusRequest();
        case CommandType::DISCONNECT:
            return handleDisconnect();
        default:
            return "Unknown command " + command;
    }
}

CommandProcessor::CommandType CommandProcessor::getCommandType(const std::string& command)
{
    if (command == "turn_led")
    {
        return CommandType::TURN_LED;
    }

    else if (command == "get_status")
    {
        return CommandType::GET_STATUS;
    }

    else if (command == "disconnect")
    {
        return CommandType::DISCONNECT;
    }

    else return CommandType::UNKNOWN;
}

std::string CommandProcessor::handlTurnLED()
{
    std::cout << "[Command] Turning LED on/off\n";
    mqttPublisher.publish("device/led", R"({"status":"LED toggled"})");


    return "LED toggled\n";
}

std::string CommandProcessor::handleStatusRequest()
{
    std::cout << "[Command] Getting the status\n"; 
    return "Status: \n";
}

std::string CommandProcessor::handleDisconnect()
{
    std::cout << "[Command] Disconnect requested\n";
    return "Disconnected, Goodbey";
}