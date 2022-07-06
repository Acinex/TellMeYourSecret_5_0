// Copyright Acinex Games 2020


#include "DetachActorFlowNode.h"

#include "FlowSubsystem.h"

UDetachActorFlowNode::UDetachActorFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Action");
#endif
}

void UDetachActorFlowNode::ExecuteInput(const FName& PinName)
{
	TSet<TWeakObjectPtr<UFlowComponent>> FlowComponents = GetFlowSubsystem()->GetComponents<UFlowComponent>(ItemIdentityTags, EGameplayContainerMatchType::All);

	if (FlowComponents.Num() != 1)
	{
		AddStatusReport(TEXT("The Identifier is not unique or does not exist"));
		return TriggerFirstOutput(true);
	}

	const TWeakObjectPtr<UFlowComponent> FlowComponent = FlowComponents[FSetElementId::FromInteger(0)];

	AActor* Actor = FlowComponent.IsValid() ? FlowComponent->GetOwner() : nullptr;

	if (!IsValid(Actor))
	{
		return TriggerFirstOutput(true);
	}

	Actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	if (UStaticMeshComponent* StaticMeshComponent = Actor->FindComponentByClass<UStaticMeshComponent>())
	{
		StaticMeshComponent->SetSimulatePhysics(bSimulatePhysics);
	}

	return TriggerFirstOutput(true);
}

#if WITH_EDITOR
FString UDetachActorFlowNode::GetNodeDescription() const
{
	return Super::GetNodeDescription() + LINE_TERMINATOR + GetIdentityTagsDescription(ItemIdentityTags);
}
#endif
