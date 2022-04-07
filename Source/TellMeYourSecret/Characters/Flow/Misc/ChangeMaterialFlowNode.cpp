// Copyright Acinex Games 2020

#include "ChangeMaterialFlowNode.h"

UChangeMaterialFlowNode::UChangeMaterialFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif
}

void UChangeMaterialFlowNode::ExecuteInput(const FName& PinName)
{
	AActor* Actor = FindActor();
	if (!Actor)
	{
		return;
	}

	TArray<UMeshComponent*> Components;
	Actor->GetComponents<UMeshComponent>(Components);

	for (int32 Index = 0; Index < Components.Num(); Index++)
	{
		if (!Materials.IsValidIndex(Index))
		{
			return AddStatusReport(FString::Printf(TEXT("This Actor (%s) has (%i) Meshes but only (%i) are defined"), *Actor->GetName(), Components.Num(), Materials.Num()));
		}

		UMeshComponent* Component     = Components[Index];
		FMaterialArray  MaterialArray = Materials[Index];

		for (int32 MaterialIndex = 0; MaterialIndex < MaterialArray.Materials.Num(); MaterialIndex++)
		{
			Component->SetMaterial(MaterialIndex, MaterialArray.Materials[MaterialIndex]);
		}
	}

	TriggerFirstOutput(true);
}
