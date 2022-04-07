// Copyright Acinex Games 2020

#include "PauseDailyRoutineFlowNode.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

UPauseDailyRoutineFlowNode::UPauseDailyRoutineFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif
}

void UPauseDailyRoutineFlowNode::ExecuteInput(const FName& PinName)
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
		Controller->GetBlackboardComponent()->GetBrainComponent()->PauseLogic(TEXT("User interacted"));
	}

	TriggerFirstOutput(true);
}
