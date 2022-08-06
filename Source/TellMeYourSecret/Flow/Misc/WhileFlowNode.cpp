#include "WhileFlowNode.h"

UWhileFlowNode::UWhileFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif

	InputPins.Add({TEXT("Break"), TEXT("Stop repetition and call Out on next cycle")});

	OutputPins.Empty();
	OutputPins.Add({TEXT("Do"), TEXT("Repeatedly called whenever start it Called")});
	OutputPins.Add({TEXT("Out"), TEXT("Called once Do was called after Break was called")});
}

void UWhileFlowNode::ExecuteInput(const FName& PinName)
{	
	if (PinName == TEXT("Break"))
	{
		bBreak = true;
	}
	else if (bBreak)
	{
		TriggerOutput(TEXT("Out"), true);
	}
	else
	{
		TriggerOutput(TEXT("Do"));
	}
}
