// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueContainer.generated.h"

class UTellMeYourSecretGameInstance;
class UCharacterData;
class UDialogueOption;
class URichTextBlock;
class UTextBlock;
class UButton;
class UPanelWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FOptionChosen, const int32);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TELLMEYOURSECRET_API UDialogueContainer : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetDialogue(UCharacterData* Character, const FText Message, const TArray<FText> Answers);

	UFUNCTION(BlueprintCallable)
	void ChooseDialogueOption(int32 Index);

	virtual void NativeOnInitialized() override;

	FOptionChosen OnOptionChosen;

protected:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UPanelWidget* DialogueOptionsContainer;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* DialogueClickToContinue;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	URichTextBlock* DialogueText;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* SpeakerName;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UDialogueOption* Option0;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UDialogueOption* Option1;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UDialogueOption* Option2;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UDialogueOption* Option3;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UDialogueOption* Option4;
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UDialogueOption* Option5;
	UPROPERTY()
	bool bShowUnselectableOptions;
	UPROPERTY()
	FString CurrentText;
	UPROPERTY()
	FString TargetText;

	UPROPERTY()
	UTellMeYourSecretGameInstance* GameInstance;

	UPROPERTY()
	TArray<FText> Options;

private:
	void ShowOptions() const;
	UFUNCTION()
	void Continue();

	FText FormatText(const FText Input) const;
};
