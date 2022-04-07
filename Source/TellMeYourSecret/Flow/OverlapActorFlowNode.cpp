// Copyright Acinex Games 2020

#include "OverlapActorFlowNode.h"

#include "FlowComponent.h"

UOverlapActorFlowNode::UOverlapActorFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif
}

void UOverlapActorFlowNode::ExecuteInput(const FName& PinName)
{
	if (OverlappedActorTag.IsValid())
	{
		Super::ExecuteInput(PinName);
	}
	else
	{
		LogError("Missing Overlapped Actor Tag");
	}
}

void UOverlapActorFlowNode::ObserveActor(TWeakObjectPtr<AActor> Actor, TWeakObjectPtr<UFlowComponent> Component)
{
	if (!RegisteredActors.Contains(Actor))
	{
		RegisteredActors.Emplace(Actor, Component.Get());

		AActor* Owner = Component->GetOwner();

		TWeakObjectPtr<UOverlapActorFlowNode> SelfWeakPtr(this);
		Owner->OnActorBeginOverlap.AddDynamic(this, &UOverlapActorFlowNode::OnOverlap);
	}
}

void UOverlapActorFlowNode::ForgetActor(TWeakObjectPtr<AActor> Actor, const TWeakObjectPtr<UFlowComponent> Component)
{
	AActor* Owner = Component->GetOwner();
	Owner->OnActorBeginOverlap.RemoveAll(this);
}

void UOverlapActorFlowNode::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UFlowComponent* OtherFlowComponent = OtherActor->FindComponentByClass<UFlowComponent>();

	if (IsValid(OtherFlowComponent) && OtherFlowComponent->IdentityTags.HasTagExact(OverlappedActorTag))
	{
		OnEventReceived();
	}
}
