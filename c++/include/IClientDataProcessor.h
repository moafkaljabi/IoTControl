/*


2025

This class is intended to help with the seperation of concerns.

IClientDataProcessor.h

*/


#pragma once 

#include <string>
#include "rapidjson/document.h"


class IClientDataProcessor {

public:


    virtual ~IClientDataProcessor() = default;

    virtual std::string processCommand(rapidjson::Document& jsonData) = 0;

};