// Copyright Acinex Games 2020


#include "WaitForInteractionFlowNode.h"

#include "FlowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/InteractSubSystem.h"

UWaitForInteractionFlowNode::UWaitForInteractionFlowNode()
{
	OutputPins.Emplace(TEXT("Complete"));
}

void UWaitForInteractionFlowNode::ExecuteInput(const FName& PinName)
{
	UInteractSubSystem* InteractSubSystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UInteractSubSystem>();

	InteractSubSystem->OnInteract.AddDynamic(this, &UWaitForInteractionFlowNode::Interacted);
	TriggerFirstOutput(false);
}

void UWaitForInteractionFlowNode::Cleanup()
{
	UInteractSubSystem* InteractSubSystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UInteractSubSystem>();

	InteractSubSystem->OnInteract.RemoveDynamic(this, &UWaitForInteractionFlowNode::Interacted);
}

void UWaitForInteractionFlowNode::Interacted(AInteractiveObject* Object, const FGameplayTagContainer& Identity)
{
	const UInteractSubSystem* InteractSubSystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UInteractSubSystem>();

	if (InteractSubSystem->FindObject(IdentityTags, EGameplayContainerMatchType::All) == Object && Identity == User)
	{
		TriggerOutput(TEXT("Complete"), true);
	}
}
