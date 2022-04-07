#include "AbstractReputationCheckFlowNode.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

UAbstractReputationCheckFlowNode::UAbstractReputationCheckFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
	NodeStyle = EFlowNodeStyle::Condition;
#endif

#if WITH_EDITOR
	Category = TEXT("Reputation");
#endif

	OutputPins.Empty();
	OutputPins.Append({TEXT("True"), TEXT("False")});
}

void UAbstractReputationCheckFlowNode::ExecuteInput(const FName& PinName)
{
	CachedNonPlayerComponent = FindNonPlayer();
	if (Check(CachedNonPlayerComponent))
	{
		TriggerOutput(TEXT("True"), true);
	}
	else
	{
		TriggerOutput(TEXT("False"), true);
	}
}
#if WITH_EDITOR
FString UAbstractReputationCheckFlowNode::GetStatusString() const
{
	if (CachedNonPlayerComponent.IsValid())
	{
		return FString::FromInt(CachedNonPlayerComponent->GetReputation());
	}

	return FString();
}
#endif

bool UAbstractReputationCheckFlowNode::Check(const TWeakObjectPtr<UNonPlayerComponent, FWeakObjectPtr>& NonPlayerComponent) const
{
	return false;
}
