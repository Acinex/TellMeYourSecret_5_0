// Copyright Acinex Games 2020

#include "DisableMovementFlowNode.h"

#include "GameFramework/MovementComponent.h"

UDisableMovementFlowNode::UDisableMovementFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif
}

void UDisableMovementFlowNode::ExecuteInput(const FName& PinName)
{
	AActor* Actor = FindActor();

	if (!IsValid(Actor))
	{
		return;
	}

	UMovementComponent* MovementComponent = Actor->FindComponentByClass<UMovementComponent>();
	if (!IsValid(MovementComponent))
	{
		return AddStatusReport(TEXT("Actor has no MovementComponent"));
	}

	if (bEnable)
	{
		MovementComponent->Activate();
	}
	else
	{
		MovementComponent->Deactivate();
	}

	TriggerFirstOutput(true);
}
