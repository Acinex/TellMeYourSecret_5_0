// Copyright Acinex Games 2020

#include "HasLowerReputationFlowNode.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#if WITH_EDITOR
FString UHasLowerReputationFlowNode::GetNodeDescription() const
{
	return FString::Printf(TEXT("Lower than %i"), Reputation);
}
#endif

bool UHasLowerReputationFlowNode::Check(const TWeakObjectPtr<UNonPlayerComponent>& NonPlayerComponent) const
{
	return NonPlayerComponent->GetReputation() < Reputation;
}
