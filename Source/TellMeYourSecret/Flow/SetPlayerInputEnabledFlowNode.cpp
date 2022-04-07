// Copyright Acinex Games 2020

#include "SetPlayerInputEnabledFlowNode.h"

USetPlayerInputEnabledFlowNode::USetPlayerInputEnabledFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif
}

void USetPlayerInputEnabledFlowNode::ExecuteInput(const FName& PinName)
{
	APlayerController* FirstPlayerController = GetWorld()->GetFirstPlayerController();

	if (bEnabled)
	{
		FirstPlayerController->GetPawn()->EnableInput(FirstPlayerController);
	}
	else
	{
		FirstPlayerController->GetPawn()->DisableInput(FirstPlayerController);
	}

	TriggerFirstOutput(true);
}

#if WITH_EDITOR
FString USetPlayerInputEnabledFlowNode::GetNodeDescription() const
{
	if (bEnabled)
	{
		return TEXT("Enable Player Input");
	}

	return TEXT("Disable Player Input");
}
#endif
