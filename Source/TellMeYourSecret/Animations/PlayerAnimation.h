// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimation.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UPlayerAnimation : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsShowingSmartphone;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsFirstPerson;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsCrouching;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Direction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRotator HeadRotation;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintCallable)
	void LeftFootStep();
	UFUNCTION(BlueprintCallable)
	void RightFootStep();

	UFUNCTION(BlueprintImplementableEvent)
	USoundBase* SelectSurfaceSound(EPhysicalSurface Surface);
};
