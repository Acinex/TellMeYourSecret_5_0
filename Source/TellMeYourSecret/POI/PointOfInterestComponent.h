// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "PointOfInterest.h"
#include "Components/ActorComponent.h"
#include "PointOfInterestComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API UPointOfInterestComponent : public UActorComponent, public IPointOfInterest
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPointOfInterestComponent();

	virtual FVector FindRandomSpot_Implementation() override;

	virtual const FGameplayTagContainer GetIdentifier_Implementation() const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer Identity;
};
