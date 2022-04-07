// Copyright Acinex Games 2020

#include "RotateActorFlowNode.h"

#include "Kismet/KismetMathLibrary.h"
#include "TellMeYourSecret/Log.h"

URotateActorFlowNode::URotateActorFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Action");
#endif
}

void URotateActorFlowNode::ExecuteInput(const FName& PinName)
{
	AActor* Actor = FindActor();
	if (!IsValid(Actor))
	{
		return;
	}

	AActor* Target = FindActor(TargetIdentityTags);

	if (!IsValid(Target))
	{
		return;
	}

	FRotator FindLookAtRotation = UKismetMathLibrary::FindLookAtRotation(Actor->GetActorLocation(), Target->GetActorLocation());
	FindLookAtRotation          = {0, FindLookAtRotation.Yaw, 0};

	Actor->SetActorRotation(FindLookAtRotation);

	TriggerFirstOutput(true);
}

#if WITH_EDITOR
FString URotateActorFlowNode::GetNodeDescription() const
{
	return Super::GetNodeDescription() + LINE_TERMINATOR + GetIdentityTagsDescription(TargetIdentityTags);
}

AActor* URotateActorFlowNode::GetActorToFocus()
{
	return FindActor(TargetIdentityTags);
}
#endif
