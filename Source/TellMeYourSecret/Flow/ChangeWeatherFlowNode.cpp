// Copyright Acinex Games 2020


#include "ChangeWeatherFlowNode.h"

UChangeWeatherFlowNode::UChangeWeatherFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif
}

void UChangeWeatherFlowNode::ExecuteInput(const FName& PinName)
{
	Super::ExecuteInput(PinName);
}

FString UChangeWeatherFlowNode::GetNodeDescription() const
{
	return Super::GetNodeDescription();
}
