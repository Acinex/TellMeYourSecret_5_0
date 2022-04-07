// Copyright Acinex Games 2020

#include "HasHigherReputationFlowNode.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

#if WITH_EDITOR
FString UHasHigherReputationFlowNode::GetNodeDescription() const
{
	return FString::Printf(TEXT("Higher than %i"), Reputation);
}
#endif

bool UHasHigherReputationFlowNode::Check(const TWeakObjectPtr<UNonPlayerComponent, FWeakObjectPtr>& NonPlayerComponent) const
{
	return NonPlayerComponent->GetReputation() > Reputation;
}
