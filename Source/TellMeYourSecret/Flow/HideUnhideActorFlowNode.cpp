// Copyright Acinex Games 2020


#include "HideUnhideActorFlowNode.h"

#include "GameFramework/Actor.h"

UHideUnhideActorFlowNode::UHideUnhideActorFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif
}

void UHideUnhideActorFlowNode::ExecuteInput(const FName& PinName)
{
	AActor* Actor = FindActor();
	if (IsValid(Actor))
	{
		Actor->SetActorHiddenInGame(bHidden);
	}
}
