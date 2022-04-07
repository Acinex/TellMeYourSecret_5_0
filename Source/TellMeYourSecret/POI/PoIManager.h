// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"

#include "PoIManager.generated.h"

UCLASS()
class TELLMEYOURSECRET_API UPoIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UPoIManager();

	UFUNCTION(BlueprintCallable)
	void Register(UObject* PointOfInterest);

	UFUNCTION(BlueprintPure)
	FVector FindRandomSpot(const FGameplayTagContainer Identifier) const;
	UFUNCTION(BlueprintPure)
	FVector FindRandomSpotForActor(const FGameplayTagContainer Identifier, AActor* Actor) const;

private:
	TMultiMap<FGameplayTag, TWeakObjectPtr<UObject>> PointsOfInterest;

	UObject* FindPoi(const FGameplayTagContainer Identifier) const;
};
