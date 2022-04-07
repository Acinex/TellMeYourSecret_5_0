// Copyright Acinex Games 2020

#include "NonPlayerComponentFlowNode.h"

#include "FlowAsset.h"
#include "FlowSubsystem.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

UNonPlayerComponentFlowNode::UNonPlayerComponentFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

TWeakObjectPtr<UNonPlayerComponent> UNonPlayerComponentFlowNode::FindNonPlayer() const
{
	return FindComponent<UNonPlayerComponent>();
}

TWeakObjectPtr<UCharacterComponent> UNonPlayerComponentFlowNode::FindCharacter() const
{
	return FindComponent<UCharacterComponent>();
}

template <class T>
TWeakObjectPtr<T> UNonPlayerComponentFlowNode::FindComponent() const
{
	static_assert(TPointerIsConvertibleFromTo<T, const UCharacterComponent>::Value, "'T' template parameter to GetComponents must be derived from UCharacterComponent");

	if (!IdentityTags.IsValid())
	{
		return Cast<T>(GetFlowAsset()->GetOwner());
	}

	for (const TWeakObjectPtr<UFlowComponent>& FoundComponent : GetFlowSubsystem()->GetComponents<UFlowComponent>(IdentityTags, EGameplayContainerMatchType::All))
	{
		return Cast<T>(FoundComponent);
	}

	return nullptr;
}
