// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommonActivatableWidget.h"
#include "TellMeYourSecret/UMG/TMYSButton.h"
#include "ConfirmDialogue.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResponse, bool, Result);

class UUIBase;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UConfirmDialogue : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	UFUNCTION(BlueprintCallable)
	void Setup(FText InTitle, FText InMessage, UUIBase* InOwner, int32 InIndex);

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

	UPROPERTY()
	UUIBase* Owner;

	int32 Index;

	UFUNCTION()
	virtual void Cancel();

	UFUNCTION()
	virtual void Confirm();
};
