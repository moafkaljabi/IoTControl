#include "CommandProcessor.h"
#include "MQTTPublisher.h"
#include <iostream>

CommandProcessor::CommandProcessor(MQTTPublisher* mqttPublisher)
    : mqttPublisher(mqttPublisher) {}

std::string CommandProcessor::processCommand(const rapidjson::Document& jsonDoc)
{
    if (!jsonDoc.HasMember("command") || !jsonDoc["command"].IsString()) {
        return "Invalid command format.";
    }

    std::string command = jsonDoc["command"].GetString();
    CommandType commandType = getCommandType(command);

    switch (commandType) {
        case CommandType::TURN_LED:
            return handleTurnLED();
        case CommandType::GET_STATUS:
            return handleStatusRequest();
        case CommandType::DISCONNECT:
            return handleDisconnect();
        default:
            return "Unknown command: " + command;
    }
}

CommandProcessor::CommandType CommandProcessor::getCommandType(const std::string& command)
{
    if (command == "turn_led") return CommandType::TURN_LED;
    if (command == "get_status") return CommandType::GET_STATUS;
    if (command == "disconnect") return CommandType::DISCONNECT;
    return CommandType::UNKNOWN;
}

std::string CommandProcessor::handleTurnLED()
{
    std::cout << "[Command] Turning LED on/off\n";
    if (mqttPublisher) {
        mqttPublisher->publish(TOPIC_LED, R"({"status":"LED toggled"})");
    } else {
        std::cerr << "[Warning] MQTT publisher not available\n";
    }
    return "LED toggled\n";
}

std::string CommandProcessor::handleStatusRequest()
{
    std::cout << "[Command] Getting the status\n";
    return "Status: All systems nominal\n";
}

std::string CommandProcessor::handleDisconnect()
{
    std::cout << "[Command] Disconnect requested\n";
    return "Disconnected. Goodbye.";
}
