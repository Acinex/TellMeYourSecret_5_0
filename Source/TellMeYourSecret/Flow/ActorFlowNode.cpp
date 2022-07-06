// Copyright Acinex Games 2020

#include "ActorFlowNode.h"

#include "FlowAsset.h"
#include "FlowComponent.h"
#include "FlowSubsystem.h"
#include "Kismet/GameplayStatics.h"

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
	TArray<AActor*> Actors;

	for (const TWeakObjectPtr<UFlowComponent>& FoundComponent : GetFlowSubsystem()->GetComponents<UFlowComponent>(Tags, EGameplayContainerMatchType::All))
	{
		Actors.Add(FoundComponent->GetOwner());
	}

	if (Actors.Num())
	{
		if (Actors.Num() == 1)
		{
			return Actors[0];
		}

		if (const AActor* Executor = Cast<UFlowComponent>(GetFlowAsset()->GetOwner())->GetOwner())
		{
			float Distance;
			return UGameplayStatics::FindNearestActor(Executor->GetActorLocation(), Actors, Distance);
		}
	}


	AddStatusReport(TEXT("No Actor found for ") + GetIdentityTagsDescription(Tags));
	return nullptr;
}
