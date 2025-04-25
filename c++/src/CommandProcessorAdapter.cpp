/*


2025

This class is intended to help with the seperation of concerns.

CommandProcessAdapter.h

*/


#include "../include/CommandProcessorAdapter.h"
#include "rapidjson/document.h"


std::string CommandProcessAdapter::process(const std::string& rawData)
{
    rapidjson::Document document;
    document.Parse(rawData.c_str());

    return commandProcessor.processCommand(document);
}

