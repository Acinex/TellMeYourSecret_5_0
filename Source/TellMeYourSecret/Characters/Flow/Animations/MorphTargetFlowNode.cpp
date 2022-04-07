// Copyright Acinex Games 2020

#include "MorphTargetFlowNode.h"

#include "FlowAsset.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "TellMeYourSecret/Characters/Util/MorphTargetExecutor.h"

UMorphTargetFlowNode::UMorphTargetFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Animation");
#endif

	OutputPins.Add({TEXT("Complete"), TEXT("Will be executed when the animation is completed")});
}

void UMorphTargetFlowNode::ExecuteInput(const FName& PinName)
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();

	if (!NonPlayerComponent.IsValid())
	{
		return;
	}

	if (bClearMorphTargets)
	{
		NonPlayerComponent->GetMesh()->ClearMorphTargets();
	}

	Executor = NewObject<UMorphTargetExecutor>(this, TEXT("Executor"));
	Executor->OnStepFinished.AddDynamic(this, &UMorphTargetFlowNode::FinishStep);
	Counter = MorphTargets.Num();

	for (auto MorphTargetChange : MorphTargets)
	{
		Executor->AddMorphTargetChange(NonPlayerComponent.Get(), MorphTargetChange);
	}

	TriggerFirstOutput(false);
	if (!MorphTargets.Num())
	{
		Counter = 1;
		FinishStep();
	}
}

#if WITH_EDITOR
FString UMorphTargetFlowNode::GetNodeDescription() const
{
	return Super::GetNodeDescription() + LINE_TERMINATOR + Title;
}

bool UMorphTargetFlowNode::IsParametersValid() const
{
	return MorphTargets.Num() > 0;
}

FString UMorphTargetFlowNode::GetStatusString() const
{
	return Counter > 0 ? FString::FromInt(Counter) : FString();
}
#endif

void UMorphTargetFlowNode::FinishStep()
{
	Counter--;
	if (Counter == 0)
	{
		return TriggerOutput(TEXT("Complete"), true);
	}
}
