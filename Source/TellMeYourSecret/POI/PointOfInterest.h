// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "PointOfInterest.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType)
class UPointOfInterest : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TELLMEYOURSECRET_API IPointOfInterest
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	const FGameplayTagContainer GetIdentifier() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FVector FindRandomSpot();
};
