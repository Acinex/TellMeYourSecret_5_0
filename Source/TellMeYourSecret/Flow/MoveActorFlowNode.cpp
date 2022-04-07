// Copyright Acinex Games 2020

#include "MoveActorFlowNode.h"

UMoveActorFlowNode::UMoveActorFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif

	OutputPins.Add(TEXT("Complete"));
}

void UMoveActorFlowNode::ExecuteInput(const FName& PinName)
{
	AActor* Actor = FindActor();

	if (!IsValid(Actor))
	{
		return;
	}

	Start      = Actor->GetActorLocation();
	Difference = Location - Start;

	TriggerFirstOutput(false);
	if (Curve)
	{
		bTickable = true;
	}
	else
	{
		Actor->SetActorLocation(Location);
		TriggerOutput(TEXT("Complete"), true);
	}
}

#if WITH_EDITOR
FString UMoveActorFlowNode::GetNodeDescription() const
{
	return Super::GetNodeDescription() + LINE_TERMINATOR + FString::Printf(TEXT("%s to %s"), *(Curve ? FString("Animated") : FString("Teleported")), *Location.ToString());
}
#endif

void UMoveActorFlowNode::Tick(const float DeltaTime)
{
	if (!Curve)
	{
		return;
	}
	
	Time += DeltaTime;
	AActor* Actor = FindActor();
	Actor->SetActorLocation(Start + Difference * Curve->GetFloatValue(Time));

	if (FVector::Distance(Actor->GetActorLocation(), Location) < 0.01)
	{
		TriggerOutput(TEXT("Complete"), true);
		bTickable = false;
	}
}

TStatId UMoveActorFlowNode::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UMoveActorFlowNode, STATGROUP_Tickables);
}
