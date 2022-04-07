// Copyright Acinex Games 2020

#include "SpawnActorFlowNode.h"

#include "FlowComponent.h"
#include "FlowSubsystem.h"
#include "TellMeYourSecret/Components/SpawnComponent.h"

USpawnActorFlowNode::USpawnActorFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif

	InputPins.Empty();
	OutputPins.Empty();
	AddInputPins({TEXT("Spawn"), TEXT("Despawn")});
	AddOutputPins({TEXT("Spawned"), TEXT("Despawned")});
}

void USpawnActorFlowNode::ExecuteInput(const FName& PinName)
{
	if (IdentityTags.IsValid())
	{
		if (PinName == TEXT("Spawn"))
		{
			if (Spawn())
			{
				TriggerOutput(TEXT("Spawned"));
			}
			else
			{
				AddStatusReport(FString::Printf(TEXT("The Actor for %s has no SpawnComponent"), *GetIdentityTagsDescription(IdentityTags)));
			}
		}
		else if (PinName == TEXT("Despawn"))
		{
			int32 DespawnCount = 0;
			for (TWeakObjectPtr<USpawnComponent> SpawnComponent : SpawnComponents)
			{
				if (SpawnComponent.IsValid())
				{
					SpawnComponent->Despawn();
					DespawnCount++;
				}
			}

			if (DespawnCount > 0)
			{
				TriggerOutput(TEXT("Despawned"), true);
			}
		}
	}
	else
	{
		LogError(MissingIdentityTag);
	}
}

#if WITH_EDITOR
FString USpawnActorFlowNode::GetNodeDescription() const
{
	const FString ClassString = SpawnParams.ActorClass ? SpawnParams.ActorClass->GetFName().ToString() : TEXT("Missing Actor Class!");
	return GetIdentityTagsDescription(IdentityTags) + LINE_TERMINATOR + ClassString;
}
#endif

void USpawnActorFlowNode::OnSave_Implementation()
{
	for (const TWeakObjectPtr<USpawnComponent> SpawnComponent : SpawnComponents)
	{
		FTransform Transform;
		if (SpawnComponent->GetTransform(Transform))
		{
			ActorTransforms.Add(Transform);
		}
	}

	SpawnersNum = SpawnComponents.Num();
}

void USpawnActorFlowNode::OnLoad_Implementation()
{
	UFlowSubsystem* Subsystem = GetFlowSubsystem();

	if (ActorTransforms.Num())
	{
		Spawn();
		Subsystem->OnComponentRegistered.AddDynamic(this, &USpawnActorFlowNode::CheckSpawns);

		for (int32 I = 0; I < SpawnComponents.Num(); I++)
		{
			const FTransform                      ActorTransform = ActorTransforms[I];
			const TWeakObjectPtr<USpawnComponent> SpawnComponent = SpawnComponents[I];
			SpawnComponent->TransformActor(ActorTransform);
		}

		if (SpawnComponents.Num() == SpawnersNum)
		{
			TriggerOutput(TEXT("Spawned"));
		}
	}
}

void USpawnActorFlowNode::CheckSpawns(UFlowComponent* Component)
{
	if (Component->IdentityTags.HasAny(IdentityTags))
	{
		int32 SpawnCount;
		SpawnOneActor(Component, SpawnCount);
		if (SpawnComponents.Num() == SpawnersNum)
		{
			TriggerOutput(TEXT("Spawned"));
		}
	}
}

bool USpawnActorFlowNode::Spawn()
{
	bool  bFoundActors = false;
	int32 SpawnCount   = 0;
	for (const TWeakObjectPtr<UFlowComponent>& FoundComponent : GetFlowSubsystem()->GetComponents<UFlowComponent>(IdentityTags, EGameplayContainerMatchType::Any))
	{
		bFoundActors = true;
		SpawnOneActor(FoundComponent.Get(), SpawnCount);
	}

	if (!bFoundActors)
	{
		AddStatusReport(TEXT("No Spawner found for ") + GetIdentityTagsDescription(IdentityTags));
	}

	return SpawnCount > 0;
}

void USpawnActorFlowNode::SpawnOneActor(UFlowComponent* Component, int32& SpawnCount)
{
	TArray<USpawnComponent*> NewSpawnComponents;
	Component->GetOwner()->GetComponents<USpawnComponent>(NewSpawnComponents);

	for (USpawnComponent* SpawnComponent : NewSpawnComponents)
	{
		if (!SpawnComponents.Contains(SpawnComponent))
		{
			if (SpawnComponent->Spawn(SpawnParams))
			{
				SpawnComponents.Emplace(SpawnComponent);
				SpawnCount++;
			}
		}
	}
}
