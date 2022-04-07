// Copyright Acinex Games 2020

#include "SpawnComponent.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

USpawnComponent::USpawnComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	SetUsingAbsoluteScale(true);
	SetUsingAbsoluteRotation(false);
	ArrowColor = FColor::Red;
	ArrowSize  = 0.5f;
}

bool USpawnComponent::GetTransform(FTransform& Transform) const
{
	if (SpawnedActor.IsValid())
	{
		Transform = SpawnedActor->GetActorTransform();
	}

	return SpawnedActor.IsValid();
}

void USpawnComponent::TransformActor(const FTransform Transform) const
{
	if (SpawnedActor.IsValid())
	{
		SpawnedActor->SetActorTransform(Transform);
	}
}

void USpawnComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Despawn();

	Super::EndPlay(EndPlayReason);
}

bool USpawnComponent::Spawn(FSpawnParams& SpawnParams)
{
	if (SpawnParams.ActorClass->IsChildOf(APawn::StaticClass()))
	{
		SpawnedActor = UAIBlueprintHelperLibrary::SpawnAIFromClass(this, SpawnParams.ActorClass.Get(), nullptr, GetComponentLocation(), GetComponentRotation(), SpawnParams.bNoCollisionFail);
	}
	else
	{
		SpawnedActor = GetWorld()->SpawnActor(SpawnParams.ActorClass, &GetComponentTransform());
	}

	if (SpawnedActor.IsValid() && SpawnParams.ActorScale != 1.0f)
	{
		SpawnedActor->SetActorScale3D(SpawnedActor->GetActorScale3D() * SpawnParams.ActorScale);
	}

	return SpawnedActor.IsValid();
}

void USpawnComponent::Despawn()
{
	if (SpawnedActor.IsValid())
	{
		SpawnedActor->Destroy();
	}

	SpawnedActor = nullptr;
}
