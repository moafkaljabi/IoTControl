/*


2025

This class is intended to help with the seperation of concerns.

IClientDataProcessor.h

*/


// IClientDataProcessor.h
#pragma once

#include <rapidjson/document.h>

class IClientDataProcessor
{
public:
    virtual ~IClientDataProcessor() = default;
    virtual std::string processCommand(const rapidjson::Document& jsonDoc) = 0;
};
