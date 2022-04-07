// Copyright Acinex Games 2020

#include "AddForceFlowNode.h"

UAddForceFlowNode::UAddForceFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Action");
#endif
}

void UAddForceFlowNode::ExecuteInput(const FName& PinName)
{
	AActor* Actor = FindActor();

	if (!IsValid(Actor))
	{
		return;
	}

	UMeshComponent* MeshComponent = Cast<UMeshComponent>(Actor->GetRootComponent());
	if (!MeshComponent)
	{
		return AddStatusReport(FString::Printf(TEXT("The Root of %s is no MeshComponent so no force can be applied"), *Actor->GetName()));
	}

	MeshComponent->AddForce(Force, BoneName, bAccelChange);

	TriggerFirstOutput(true);
}
