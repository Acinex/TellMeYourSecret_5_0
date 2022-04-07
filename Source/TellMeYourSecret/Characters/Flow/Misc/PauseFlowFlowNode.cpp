// Copyright Acinex Games 2020

#include "PauseFlowFlowNode.h"

#include "FlowSubsystem.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

UPauseFlowFlowNode::UPauseFlowFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif
}

void UPauseFlowFlowNode::ExecuteInput(const FName& PinName)
{
	TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();

	if (!NonPlayerComponent.IsValid())
	{
		return;
	}

	UFlowSaveGame* LoadedSaveGame = GetFlowSubsystem()->GetLoadedSaveGame();

	if (LoadedSaveGame)
	{
		NonPlayerComponent->SaveRootFlow(LoadedSaveGame->FlowInstances);
		NonPlayerComponent->FinishRootFlow(EFlowFinishPolicy::Abort);
	}

	TriggerFirstOutput(true);
}
