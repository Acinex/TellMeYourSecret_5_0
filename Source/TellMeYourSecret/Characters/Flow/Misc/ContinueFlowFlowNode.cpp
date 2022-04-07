// Copyright Acinex Games 2020

#include "ContinueFlowFlowNode.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

UContinueFlowFlowNode::UContinueFlowFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif
}

void UContinueFlowFlowNode::ExecuteInput(const FName& PinName)
{
	TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();

	if (!NonPlayerComponent.IsValid())
	{
		return;
	}

	NonPlayerComponent->LoadRootFlow();
}
