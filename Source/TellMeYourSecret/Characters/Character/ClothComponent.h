// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "ClothSlot.h"
#include "Components/ActorComponent.h"
#include "ClothComponent.generated.h"

UCLASS(ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API UClothComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UClothComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintPure)
	EClothSlot GetClothSlot() const { return ClothSlot; }

	void SetClothSlot(const EClothSlot InClothSlot) { ClothSlot = InClothSlot; }

protected:
	UPROPERTY(EditDefaultsOnly)
	EClothSlot ClothSlot;
};
