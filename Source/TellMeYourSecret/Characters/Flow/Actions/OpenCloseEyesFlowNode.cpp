// Copyright Acinex Games 2020

#include "OpenCloseEyesFlowNode.h"

#include "TellMeYourSecret/Characters/Character/CharacterAnimationInstance.h"
#include "TellMeYourSecret/Characters/Character/CharacterComponent.h"

UOpenCloseEyesFlowNode::UOpenCloseEyesFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Action");
#endif
}

void UOpenCloseEyesFlowNode::ExecuteInput(const FName& PinName)
{
	const TWeakObjectPtr<UCharacterComponent> CharacterComponent = FindCharacter();
	if (!CharacterComponent.IsValid())
	{
		return;
	}

	UCharacterAnimationInstance* AnimationInstance = CharacterComponent->GetAnimInstance<UCharacterAnimationInstance>();
	if (!AnimationInstance)
	{
		return AddStatusReport(TEXT("This Character has no CharacterAnimationInstance"));
	}

	AnimationInstance->SetEyesClosed(bClose);
	TriggerFirstOutput(true);
}
