// Copyright Acinex Games 2020


#include "RunnableFlowNode.h"
#include "TellMeYourSecret/Model/Runnable.h"

void URunnableFlowNode::ExecuteInput(const FName& PinName)
{
	if (IsValid(Class))
	{
		IRunnableInterface::Execute_Run(Class->GetDefaultObject());
	}

	TriggerFirstOutput(true);
}
