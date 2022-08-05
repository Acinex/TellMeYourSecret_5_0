// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimationInstance.generated.h"

class ACharacterBase;
class UNonPlayerComponent;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UCharacterAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	void SetAnimOverride(UAnimSequenceBase* Animation, const bool bLoop);

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	ACharacterBase* Character;
	UPROPERTY(BlueprintReadOnly)
	UNonPlayerComponent* NonPlayerComponent;

	UPROPERTY(BlueprintReadOnly)
	UAnimSequenceBase* AnimationOverride;

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
	FVector RightFootEffectorLocation;
	UPROPERTY(BlueprintReadOnly, Category=Blink)
	FVector LeftFootEffectorLocation;
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EPhysicalSurface> LeftFootSurface;
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EPhysicalSurface> RightFootSurface;

	UFUNCTION(BlueprintImplementableEvent)
	USoundBase* SelectSurfaceSound(EPhysicalSurface Surface);
};
