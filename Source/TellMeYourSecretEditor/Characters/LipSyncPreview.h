// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "TellMeYourSecret/Characters/Util/Syllable.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "GameFramework/SaveGame.h"

#include "LipSyncPreview.generated.h"

class ULipSyncExecutor;
class IDetailsView;

UCLASS(BlueprintType)
class ULipSyncPreviewData : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category=Lipsync, SaveGame, meta=(TitleProperty="Syllable"))
	TArray<FSyllable> Syllables;
	UPROPERTY(EditAnywhere, Category=Lipsync, SaveGame, meta=(DisplayName=Delay))
	float LipSyncDelay;
	
	UPROPERTY(EditAnywhere, Category=Audio, SaveGame)
	USoundBase* Audio;
	UPROPERTY(EditAnywhere, Category=Audio, SaveGame, meta=(DisplayName=Delay))
	float AudioDelay;

	UPROPERTY(EditAnywhere, Category=Animation, SaveGame)
	UAnimMontage* Montage;
	UPROPERTY(EditAnywhere, Category=Animation, SaveGame)
	FName StartSectionName;
	
	UPROPERTY(EditAnywhere, SaveGame)
	FGameplayTagContainer Identity;
};

/**
 * 
 */
UCLASS(Blueprintable)
class TELLMEYOURSECRETEDITOR_API ULipSyncPreview : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

protected:
	TSharedRef<class IDetailsView> DetailsView;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* PlayButton;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USlider* DilationSlider;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ULipSyncPreviewData* PreviewData;

	UFUNCTION(BlueprintCallable)
	void Play();

private:
	UPROPERTY()
	ULipSyncExecutor* Executor;

	static const FString SaveName;
};
