// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeypadWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSucceed);

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UKeypadWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintAssignable)
	FSucceed OnSucceed;

protected:
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* Key0;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* Key1;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* Key2;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* Key3;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* Key4;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* Key5;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* Key6;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* Key7;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* Key8;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* Key9;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* BackKey;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioModernButton* ConfirmKey;
	// UPROPERTY(meta=(BindWidget))
	// UWidgetStudioText* Display;

private:
	FString Code;

	// UFUNCTION()
	// void KeyPressed(UWidgetStudioButtonBase* CallingButton);
	// UFUNCTION()
	// void Back(UWidgetStudioButtonBase* CallingButton);
	// UFUNCTION()
	// void Confirm(UWidgetStudioButtonBase* CallingButton);
};
