/*


2025

This class is intended to help with the seperation of concerns.

CommandProcessAdapter.h

*/


#pragma once 

#include "CommandProcessor.h"
#include "IClientDataProcessor.h"

#include "rapidjson/document.h"





class CommandProcessAdapter : public IClientDataProcessor {

public:

    CommandProcessorAdapter(CommandProcessor& processor) : processor(processor){}

    std::string processCommand (const rapidjson::Document& jsonData) override {
        
        return processor.processCommand(jsonData);
    } 


private:
    CommandProcessor& processor;

};





