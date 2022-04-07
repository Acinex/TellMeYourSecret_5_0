// Copyright Acinex Games 2020

#include "ActorFlowNode.h"

#include "FlowAsset.h"
#include "FlowComponent.h"
#include "FlowSubsystem.h"

#if WITH_EDITOR
FString UActorFlowNode::GetNodeDescription() const
{
	if (IdentityTags.IsValid())
	{
		return GetIdentityTagsDescription(IdentityTags);
	}

	return TEXT("The owner is the executor");
}
#endif

AActor* UActorFlowNode::FindActor()
{
	if (IdentityTags.IsValid())
	{
		return FindActor(IdentityTags);
	}

	AActor* Actor = Cast<UFlowComponent>(GetFlowAsset()->GetOwner())->GetOwner();
	if (!Actor)
	{
		AddStatusReport(TEXT("No Actor found"));
	}
	return Actor;
}

AActor* UActorFlowNode::FindActor(const FGameplayTagContainer Tags)
{
	for (const TWeakObjectPtr<UFlowComponent>& FoundComponent : GetFlowSubsystem()->GetComponents<UFlowComponent>(Tags, EGameplayContainerMatchType::All))
	{
		return FoundComponent->GetOwner();
	}

	AddStatusReport(TEXT("No Actor found for ") + GetIdentityTagsDescription(Tags));
	return nullptr;
}
