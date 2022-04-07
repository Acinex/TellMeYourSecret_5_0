// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimationInstance.generated.h"

class UNonPlayerComponent;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UCharacterAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	void SetAnimOverride(UAnimationAsset* Animation, const bool bLoop);

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeBeginPlay() override;

	void SetEyesClosed(const bool bEyesClosed)
	{
		bKeepEyesClosed = bEyesClosed;
		LastBlink       = 0;
	}

protected:
	UPROPERTY(BlueprintReadOnly)
	UNonPlayerComponent* NonPlayerComponent;

	UPROPERTY(BlueprintReadOnly)
	UAnimationAsset* AnimationOverride;

	UPROPERTY(BlueprintReadOnly)
	bool bUseOverride;

	UPROPERTY(BlueprintReadOnly)
	bool bLoopOverride;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	FVector LookAtLocation;
	UPROPERTY(BlueprintReadOnly)
	FVector EyeLookAtLocation;
	UPROPERTY(BlueprintReadOnly)
	FRotator EyeLookAtRotation;

	UPROPERTY(BlueprintReadOnly)
	bool bUseLookAt;
	UPROPERTY(BlueprintReadOnly)
	bool bUseEyeLookAt;
	UPROPERTY(BlueprintReadOnly)
	bool bKeepEyesClosed;
	UPROPERTY(BlueprintReadOnly)
	bool bIsSwimming;

	UPROPERTY(BlueprintReadOnly, Category=Blink)
	FRotator UpperEyeLidRotation;
	UPROPERTY(BlueprintReadOnly, Category=Blink)
	FRotator LowerEyeLidRotation;

	void CalculateBlink(const float DeltaSeconds);

private:
	bool  bBLinking;
	bool  bBlinkPhaseDown;
	float LastBlink;
	float NextBlink;
};
