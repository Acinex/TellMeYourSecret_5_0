// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "MorphTargetExecutor.h"
#include "PlayDialogueStruct.h"
#include "TellMeYourSecret/Characters/Util/Syllable.h"
#include "LipSyncExecutor.generated.h"

class UCharacterComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCompleted);

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API ULipSyncExecutor : public UMorphTargetExecutor
{
	GENERATED_BODY()
public:
	explicit ULipSyncExecutor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION()
	void Start(UCharacterComponent* InNonPlayerComponent, FPlayDialogueStruct Struct);

	virtual void Stop() const override;

	UPROPERTY()
	FCompleted OnCompleted;

protected:
	UPROPERTY()
	FPlayDialogueStruct Data;

	UFUNCTION()
	void FinishStep();

	void FinishLetter();

	void TriggerLetter();
	void AddPause();

private:
	UPROPERTY()
	UCharacterComponent* NonPlayerComponent;
	UPROPERTY()
	UAudioComponent* AudioComponent;
	float            CurrentDelay;
	int32            SyllableIndex;
	int32            StepsLeft;
	TArray<FName>    MorphTargets;
};
