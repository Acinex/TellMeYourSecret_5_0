// Copyright Acinex Games 2020

#include "PoIManager.h"

#include "DrawDebugHelpers.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "PointOfInterest.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Log.h"

// Sets default values
UPoIManager::UPoIManager()
{
}

void UPoIManager::Register(UObject* PointOfInterest)
{
	FGameplayTagContainer GameplayTags = IPointOfInterest::Execute_GetIdentifier(PointOfInterest);

	for (const FGameplayTag& Tag : GameplayTags)
	{
		if (Tag.IsValid())
		{
			PointsOfInterest.Emplace(Tag, PointOfInterest);
		}
	}
}

FVector UPoIManager::FindRandomSpot(const FGameplayTagContainer Identifier) const
{
	UObject* PointOfInterest = FindPoi(Identifier, nullptr);

	if (!PointOfInterest)
	{
		return FVector::ZeroVector;
	}

	return IPointOfInterest::Execute_FindRandomSpot(PointOfInterest);
}

FVector UPoIManager::FindRandomSpotForActor(const FGameplayTagContainer Identifier, AActor* Actor) const
{
	UObject* PointOfInterest = FindPoi(Identifier, Actor);

	if (!PointOfInterest)
	{
		return FVector::ZeroVector;
	}

	FVector Location;
	UNavigationPath* NavigationPath;
	uint8 Tries = 0;

	do
	{
		Location = IPointOfInterest::Execute_FindRandomSpot(PointOfInterest);

		NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(Actor, Actor->GetActorLocation(), Location);
		if (!NavigationPath->IsValid())
		{
			DrawDebugSphere(GetWorld(), Location, 60, 20, FColor::Red, true);
		}

		Tries++;
	}
	while (Tries < 100 && (!NavigationPath || !NavigationPath->IsValid()));

	NavigationPath->EnableDebugDrawing(true, FColor::White);

	return Location;
}

UObject* UPoIManager::FindPoi(const FGameplayTagContainer Identifier, const AActor* Actor) const
{
	TSet<TWeakObjectPtr<UObject>> ComponentsWithAnyTag;
	for (const FGameplayTag& Tag : Identifier)
	{
		TArray<TWeakObjectPtr<UObject>> ComponentsPerTag;
		PointsOfInterest.MultiFind(Tag, ComponentsPerTag);
		ComponentsWithAnyTag.Append(ComponentsPerTag);
	}

	TArray<UObject*> ComponentsPerTag;
	for (const TWeakObjectPtr<UObject>& Object : ComponentsWithAnyTag)
	{
		if (Object.IsValid())
		{
			FGameplayTagContainer GameplayTags = IPointOfInterest::Execute_GetIdentifier(Object.Get());
			if (GameplayTags.HasAllExact(Identifier))
			{
				ComponentsPerTag.Emplace(Object.Get());
			}
		}
	}

	if (ComponentsPerTag.Num())
	{
		if (IsValid(Actor))
		{
			TArray<AActor*> Actors;

			for (const UObject* Component : ComponentsPerTag)
			{
				Actors.Add(Cast<AActor>(Component->GetOuter()));
			}

			float Distance;
			return UGameplayStatics::FindNearestActor(Actor->GetActorLocation(), Actors, Distance);
		}

		return ComponentsPerTag[0];
	}

	return nullptr;
}
