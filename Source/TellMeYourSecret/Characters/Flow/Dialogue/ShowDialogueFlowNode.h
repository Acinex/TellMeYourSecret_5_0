// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "TellMeYourSecret/Characters/Util/Syllable.h"
#include "TellMeYourSecret/Characters/Character/CharacterComponent.h"
#include "Sound/DialogueWave.h"

#include "ShowDialogueFlowNode.generated.h"

class ULipSyncExecutor;
/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Show dialogue"))
class TELLMEYOURSECRET_API UShowDialogueFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category=Dialogue)
	FText Text;
	UPROPERTY(EditAnywhere, Category=Dialogue)
	TArray<FText> Answers;

	UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Lipsync, meta=(TitleProperty="Syllable"))
	TArray<FSyllable> Syllables;
	UPROPERTY(EditAnywhere, Category=Lipsync, meta=(DisplayName=Delay))
	float LipSyncDelay;

	UPROPERTY(EditAnywhere, Category=Audio)
	USoundBase* AudioTrack;
	UPROPERTY(EditAnywhere, Category=Audio, meta=(DisplayName=Delay))
	float AudioDelay;

	UPROPERTY(EditAnywhere, Category=Animation)
	UAnimMontage* Montage;
	UPROPERTY(EditAnywhere, Category=Animation)
	FName StartSectionName;

	UPROPERTY(EditAnywhere, Category = Identifier)
	FGameplayTagContainer PartnerIdentityTags;

public:
	static const FString Continue;

	explicit UShowDialogueFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual FString GetNodeDescription() const override;

	virtual void FixNode(UEdGraphNode* NewGraph) override;

private:
	void RefreshSyllables();

#endif
private:
	void RefreshOutputs();
protected:
	virtual void Stop() const;

private:
	TWeakObjectPtr<UCharacterComponent> CharacterComponent;
	TWeakObjectPtr<UCharacterComponent> PartnerCharacterComponent;
	float                               CurrentDelay;
	int32                               SyllableIndex;

	UPROPERTY()
	ULipSyncExecutor* LipSyncExecutor;
};
