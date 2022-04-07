// Copyright Acinex Games 2020

#include "HasBetweenReputationFlowNode.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

#if WITH_EDITOR
FString UHasBetweenReputationFlowNode::GetNodeDescription() const
{
	return FString::Printf(TEXT("Between %i and %i"), From, To);
}
#endif

bool UHasBetweenReputationFlowNode::Check(const TWeakObjectPtr<UNonPlayerComponent>& NonPlayerComponent) const
{
	return FMath::IsWithin(NonPlayerComponent->GetReputation(), From, To);
}
