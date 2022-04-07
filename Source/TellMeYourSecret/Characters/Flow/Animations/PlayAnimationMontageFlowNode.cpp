// Copyright Acinex Games 2020

#include "PlayAnimationMontageFlowNode.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

UPlayAnimationMontageFlowNode::UPlayAnimationMontageFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	InputPins.Add({TEXT("Stop"), TEXT("Stops the animation immediately")});
	OutputPins.Add({TEXT("Stopped"), TEXT("Animation is stopped by the input pin")});
}

void UPlayAnimationMontageFlowNode::ExecuteInput(const FName& PinName)
{
	if (PinName.IsEqual(TEXT("Stop")))
	{
		Stop();
		TriggerOutput(TEXT("Stopped"), true);
	}
	else
	{
		PlayAnimation();
		TriggerFirstOutput(false);
	}
}
#if WITH_EDITOR
UObject* UPlayAnimationMontageFlowNode::GetAssetToEdit()
{
	return Montage;
}
#endif

void UPlayAnimationMontageFlowNode::OnComplete()
{
	TriggerOutput(TEXT("Complete"), false);
}

void UPlayAnimationMontageFlowNode::OnAnimNotify(const FName Name)
{
	TriggerOutput(Name);
}
