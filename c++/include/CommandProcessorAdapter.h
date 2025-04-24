/*


2025

This class is intended to help with the seperation of concerns.

CommandProcessAdapter.h

*/


#pragma once 

#include "CommandProcessor.h"
#include "IClientDataProcessor.h"




class CommandProcessAdapter : public IClientDataProcessor {

public:

    CommandProcessorAdapter(CommandProcessor& processor)
        : commandProcessor(processor);

    std::string(const std::string rawData) override;


private:
    

};