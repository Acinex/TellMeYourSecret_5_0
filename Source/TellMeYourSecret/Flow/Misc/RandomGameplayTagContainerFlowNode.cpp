// Copyright Acinex Games 2020


#include "RandomGameplayTagContainerFlowNode.h"

URandomGameplayTagContainerFlowNode::URandomGameplayTagContainerFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif
}

void URandomGameplayTagContainerFlowNode::ExecuteInput(const FName& PinName)
{
	Selected = Tags[FMath::RandRange(0, Tags.Num() - 1)];

	AddStatusReport(TEXT("Selected ") + Selected.ToString());

	TriggerFirstOutput(true);
}

#if WITH_EDITOR
bool URandomGameplayTagContainerFlowNode::IsParametersValid() const
{
	return Tags.Num() > 0;
}
#endif
