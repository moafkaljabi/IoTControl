/*

2025

*/


#include "CommandProcessorAdapterFactory.h"

CommandProcessorAdapterFactory::CommandProcessorAdapterFactory(CommandProcessor& commandProcessor)
    : commandProcessor(commandProcessor){}

    std::unique_ptr CommandProcessorAdapterFactory::createProcessor()
    {
        return std::make_unique<CommandProcessorAdapterFactory>
    }
