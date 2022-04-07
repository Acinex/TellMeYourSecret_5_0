// Copyright Acinex Games 2020

#include "ChangeReputationFlowNode.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "TellMeYourSecret/Characters/ReputationSystem.h"
#include "Kismet/GameplayStatics.h"

UChangeReputationFlowNode::UChangeReputationFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Reputation");
#endif
}

void UChangeReputationFlowNode::ExecuteInput(const FName& PinName)
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();
	if (!IsValid(NonPlayerComponent.Get()))
	{
		Finish();
		return;
	}

	UReputationSystem* ReputationSystem = UGameplayStatics::GetGameInstance(NonPlayerComponent.Get())->GetSubsystem<UReputationSystem>();

	ReputationSystem->ChangeReputation(NonPlayerComponent->CharacterData->Identifier, ReputationChange);

	TriggerFirstOutput(true);
}

#if WITH_EDITOR
FString UChangeReputationFlowNode::GetNodeDescription() const
{
	FString Description = TEXT("Reputation ");

	if (ReputationChange >= 0)
	{
		Description.Append("+");
	}

	Description.Append(FString::FromInt(ReputationChange));

	return Super::GetNodeDescription() + LINE_TERMINATOR + Description;
}
#endif
