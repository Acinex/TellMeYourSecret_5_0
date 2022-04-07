// Copyright Acinex Games 2020

#include "InteractFlowNode.h"

#include "AIController.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Actors/Interact/StatefulInteractiveObject.h"
#include "TellMeYourSecret/GameInstances/InteractSubSystem.h"

class UQuestManager;

UInteractFlowNode::UInteractFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Action");
#endif

	OutputPins.Add({TEXT("Locked"), TEXT("The selected Object cant be used because it's locked for this actor")});
}

void UInteractFlowNode::ExecuteInput(const FName& PinName)
{
	InteractiveObject = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UInteractSubSystem>()->FindObject(InteractionIdentityTags, EGameplayContainerMatchType::All);

	NonPlayerComponent = FindNonPlayer();

	if (!NonPlayerComponent.IsValid())
	{
		return;
	}

	if (!IsValid(InteractiveObject) || InteractiveObject->IsLocked(NonPlayerComponent->IdentityTags))
	{
		AddStatusReport(TEXT("Locked!"));
		return TriggerOutput(TEXT("Locked"), true);
	}

	Controller = Cast<AAIController>(Cast<APawn>(NonPlayerComponent->GetOwner())->GetController());

	ApproachAction = NewObject<UApproachAction>(this);
	ApproachAction->OnComplete.AddUObject(this, &UInteractFlowNode::PlayAnimation);

	if (ApproachAction->Approach(InteractiveObject, Controller, NonPlayerComponent))
	{
		TriggerFirstOutput(false);
	}
	else
	{
		AddStatusReport(TEXT("No appropriate Approach found"));
	}
}

void UInteractFlowNode::OnAnimNotify(const FName Name)
{
	if (Name == TEXT("Interact") && IsValid(InteractiveObject))
	{
		InteractiveObject->Interact(NonPlayerComponent->IdentityTags, FLatentActionInfo());
	}
}

void UInteractFlowNode::OnComplete()
{
	TriggerOutput(TEXT("Complete"), true);
}

#if WITH_EDITOR
FString UInteractFlowNode::GetNodeDescription() const
{
	return Super::GetNodeDescription() + LINE_TERMINATOR + GetIdentityTagsDescription(InteractionIdentityTags);
}
#endif
