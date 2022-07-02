// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Components/ArrowComponent.h"

#include "ApproachComponent.generated.h"

UCLASS(ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API UApproachComponent final : public UArrowComponent
{
	GENERATED_BODY()

public:
	UApproachComponent();

	bool IsFor(const FGameplayTagContainer Other) const;
	bool IsForAll() const;

	bool IsOccupied() const;

	void SetOccupied(const bool InbOccupied);

protected:
	/** Character contained in this Tag can use this. Keep empty if its for everyone */
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer Tags;

	bool bOccupied;
};
