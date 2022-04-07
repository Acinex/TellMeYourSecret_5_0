#pragma once
#include "Syllable.h"
#include "PlayDialogueStruct.generated.h"

USTRUCT(BlueprintType)
struct TELLMEYOURSECRET_API FPlayDialogueStruct
{
	GENERATED_BODY()

	UPROPERTY()
	USoundBase* Audio;
	UPROPERTY()
	float AudioDelay;

	UPROPERTY()
	TArray<FSyllable> Syllables;
	UPROPERTY()
	float LipSyncDelay;

	UPROPERTY()
	UAnimMontage* Montage;
	UPROPERTY()
	FName StartSectionName;
};
