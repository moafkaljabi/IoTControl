/*

2025

*/

#pragma once

#include "IClientDataProcessorFactory.h"
#include "CommandProcessor.h"

class CommandProcessorAdapterFactory : public IClientDataProcessorFactory
{
public:
    CommandProcessorAdapterFactory(CommandProcessor& commandProcessor);
    std::unique_ptr<IClientDataProcessor> createProcessor() override;

private:
    CommandProcessor& commandProcessor;
};
