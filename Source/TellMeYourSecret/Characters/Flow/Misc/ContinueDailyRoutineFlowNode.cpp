// Copyright Acinex Games 2020

#include "ContinueDailyRoutineFlowNode.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

UContinueDailyRoutineFlowNode::UContinueDailyRoutineFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif
}

void UContinueDailyRoutineFlowNode::ExecuteInput(const FName& PinName)
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();

	if (!NonPlayerComponent.IsValid())
	{
		return TriggerFirstOutput(true);
	}

	APawn* Pawn = Cast<APawn>(NonPlayerComponent->GetOwner());
	if (!Pawn)
	{
		return TriggerFirstOutput(true);
	}

	AAIController* Controller = Cast<AAIController>(Pawn->GetController());

	if (Controller)
	{
		Controller->GetBlackboardComponent()->GetBrainComponent()->ResumeLogic(TEXT("User interaction complete"));
	}

	TriggerFirstOutput(true);
}
