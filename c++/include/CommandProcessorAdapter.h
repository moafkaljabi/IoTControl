/*


2025

This class is intended to help with the seperation of concerns.

CommandProcessAdapter.h

*/


#pragma once 

#include <rapidjson/document.h>
#include "CommandProcessor.h"
#include "IClientDataProcessor.h"



class CommandProcessAdapter : public IClientDataProcessor {

public:

    CommandProcessAdapter(CommandProcessor& processor)
        : processor(processor) {}

    std::string processCommand (const rapidjson::Document& jsonData) override {
        
        return processor.processCommand(jsonData);
    } 


private:
    CommandProcessor& processor;

};


