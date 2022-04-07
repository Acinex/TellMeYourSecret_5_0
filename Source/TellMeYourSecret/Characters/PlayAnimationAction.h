#pragma once

#include "CoreMinimal.h"
#include "Engine/LatentActionManager.h"
#include "LatentActions.h"

class FPlayAnimationAction : public FPendingLatentAction
{
	float           TimeRemaining;
	bool            bMontageEnded = false;
	FName           ExecutionFunction;
	int32           OutputLink;
	FWeakObjectPtr  CallbackTarget;
	FOnMontageEnded MontageEndedDelegate;
	UAnimMontage*   AnimationMontage = nullptr;

public:
	FPlayAnimationAction(ACharacter* Character, UAnimationAsset* Animation, const FLatentActionInfo& LatentInfo);
	FPlayAnimationAction(ACharacter* Character, UAnimMontage* Animation, FName StartSectionName, const float TimeToStartMontageAt, const FLatentActionInfo& LatentInfo);

	virtual void UpdateOperation(FLatentResponse& Response) override;

private:
	float PlayMontage(ACharacter* Character, UAnimMontage* AnimMontage, const FName StartSectionName, const float TimeToStartMontageAt);
};
