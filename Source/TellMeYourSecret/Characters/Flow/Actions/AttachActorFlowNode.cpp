// Copyright Acinex Games 2020

#include "AttachActorFlowNode.h"

#include "FlowSubsystem.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

UAttachActorFlowNode::UAttachActorFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Action");
#endif
}

void UAttachActorFlowNode::ExecuteInput(const FName& PinName)
{
	Attach();
	TriggerFirstOutput(true);
}

void UAttachActorFlowNode::OnLoad_Implementation()
{
	if (AttachedItem.IsValid())
	{
		Attach();
	}
}

#if WITH_EDITOR
FString UAttachActorFlowNode::GetNodeDescription() const
{
	return Super::GetNodeDescription() + LINE_TERMINATOR + GetIdentityTagsDescription(ItemIdentityTags);
}
#endif

void UAttachActorFlowNode::Attach()
{
	const AActor* Actor = FindActor();

	if (!IsValid(Actor))
	{
		return;
	}

	USceneComponent* Parent = Actor->FindComponentByClass<USkeletalMeshComponent>();

	if (!IsValid(Parent))
	{
		Parent = Actor->GetDefaultAttachComponent();
	}

	TSet<TWeakObjectPtr<UFlowComponent>> FlowComponents = GetFlowSubsystem()->GetComponents<UFlowComponent>(ItemIdentityTags, EGameplayContainerMatchType::All);

	for (const TWeakObjectPtr<UFlowComponent> FlowComponent : FlowComponents)
	{
		AActor* Item = FlowComponent->GetOwner();

		AttachedItem = TWeakObjectPtr<AActor>(Item);

		if (UStaticMeshComponent* StaticMeshComponent = Item->FindComponentByClass<UStaticMeshComponent>())
		{
			StaticMeshComponent->SetSimulatePhysics(false);
		}

		Item->AttachToComponent(Parent, FAttachmentTransformRules(AttachmentRule, AttachmentRule, EAttachmentRule::KeepWorld, true), SocketName);
		if (AttachmentRule != EAttachmentRule::KeepWorld)
		{
			Item->SetActorRelativeRotation(Rotation);
			Item->SetActorRelativeLocation(Translate);
		}

		AddStatusReport(TEXT("Attached"));

		return;
	}
}
