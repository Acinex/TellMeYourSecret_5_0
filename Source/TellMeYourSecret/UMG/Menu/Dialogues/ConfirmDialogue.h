// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TellMeYourSecret/UMG/TMYSButton.h"
#include "ConfirmDialogue.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResponse, bool, Result);

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UConfirmDialogue : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly)
	FText Title;
	UPROPERTY(BlueprintReadOnly)
	FText Message;
	UPROPERTY(BlueprintReadOnly)
	FText ConfirmText = NSLOCTEXT("UI", "Confirm", "Yes");
	UPROPERTY(BlueprintReadOnly)
	FText CancelText = NSLOCTEXT("UI", "Cancel", "No");

	FResponse OnResponse;

protected:
	UPROPERTY(meta=(BindWidget))
	UTMYSButton* CancelButton;
	UPROPERTY(meta=(BindWidget))
	UTMYSButton* ConfirmButton;

	UFUNCTION()
	virtual void Cancel();

	UFUNCTION()
	virtual void Confirm();
};
