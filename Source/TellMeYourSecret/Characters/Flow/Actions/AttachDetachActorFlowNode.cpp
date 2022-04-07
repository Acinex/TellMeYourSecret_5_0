// Copyright Acinex Games 2020

#include "AttachDetachActorFlowNode.h"

#include "FlowSubsystem.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "TellMeYourSecret/Log.h"

UAttachDetachActorFlowNode::UAttachDetachActorFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Action");
#endif

	InputPins.Empty();
	InputPins.Emplace(TEXT("Attach"), TEXT("Attaches the actor to the chosen hand"));
	InputPins.Emplace(TEXT("Detach"), TEXT("Detached the actor from the chosen hand"));

	OutputPins.Empty();
	OutputPins.Emplace(TEXT("Attached"), TEXT("Actor is attached to the chosen hand"));
	OutputPins.Emplace(TEXT("Detached"), TEXT("Actor is detached from the chosen hand"));
}

void UAttachDetachActorFlowNode::ExecuteInput(const FName& PinName)
{
	if (TEXT("Attach") == PinName)
	{
		Attach();
	}

	if (TEXT("Detach") == PinName)
	{
		if (AttachedItem.IsValid())
		{
			AttachedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			UStaticMeshComponent* StaticMeshComponent = AttachedItem->FindComponentByClass<UStaticMeshComponent>();
			if (StaticMeshComponent)
			{
				StaticMeshComponent->SetSimulatePhysics(bSimulatePhysics);
			}
		}

		AttachedItem = nullptr;
		TriggerOutput(TEXT("Detached"), true);
		ClearStatusReport();
	}
}

void UAttachDetachActorFlowNode::OnLoad_Implementation()
{
	if (AttachedItem.IsValid())
	{
		Attach();
	}
}

#if WITH_EDITOR
FString UAttachDetachActorFlowNode::GetNodeDescription() const
{
	return Super::GetNodeDescription() + LINE_TERMINATOR + GetIdentityTagsDescription(ItemIdentityTags);
}
#endif

void UAttachDetachActorFlowNode::Attach()
{
	AActor* Actor = FindActor();

	if (!IsValid(Actor))
	{
		return Finish();
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

		UStaticMeshComponent* StaticMeshComponent = Item->FindComponentByClass<UStaticMeshComponent>();
		if (StaticMeshComponent)
		{
			bSimulatePhysics = StaticMeshComponent->IsSimulatingPhysics();
			StaticMeshComponent->SetSimulatePhysics(false);
		}

		Item->AttachToComponent(Parent, FAttachmentTransformRules(AttachmentRule, AttachmentRule, EAttachmentRule::KeepWorld, true), SocketName);
		if (AttachmentRule != EAttachmentRule::KeepWorld)
		{
			Item->SetActorRelativeRotation(Rotation);
			Item->SetActorRelativeLocation(Translate);
		}
		TriggerOutput(TEXT("Attached"));
		AddStatusReport(TEXT("Attached"));

		return;
	}
}
