// Copyright Acinex Games 2020

#pragma once

#include <Components/Button.h>

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "ConfirmDialogue.generated.h"

class UWidgetStudioButtonBase;
class UWidgetStudioModernButton;

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
	UButton* CancelButton;
	UPROPERTY(meta=(BindWidget))
	UButton* ConfirmButton;

	UFUNCTION()
	virtual void Cancel();

	UFUNCTION()
	virtual void Confirm();
};
