#pragma once

#include <string>
#include "rapidjson/document.h"

class MQTTPublisher;

class CommandProcessor {
public:
    explicit CommandProcessor(MQTTPublisher* mqttPublisher = nullptr);
    std::string processCommand(const rapidjson::Document& jsonDoc);

private:
    enum class CommandType {
        TURN_LED,
        GET_STATUS,
        DISCONNECT,
        UNKNOWN
    };

    CommandType getCommandType(const std::string& command);

    std::string handleTurnLED();
    std::string handleStatusRequest();
    std::string handleDisconnect();

    MQTTPublisher* mqttPublisher;

    static constexpr const char* TOPIC_LED = "device/led";
};
