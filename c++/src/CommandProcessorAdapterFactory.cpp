/*

2025

*/


#include "CommandProcessorAdapterFactory.h"
#include "CommandProcessorAdapter.h"

CommandProcessorAdapterFactory::CommandProcessorAdapterFactory(CommandProcessor& commandProcessor)
    : commandProcessor(commandProcessor)
{
}

std::unique_ptr<IClientDataProcessor> CommandProcessorAdapterFactory::createProcessor()
{
    return std::make_unique<CommandProcessAdapter>(commandProcessor);
}
