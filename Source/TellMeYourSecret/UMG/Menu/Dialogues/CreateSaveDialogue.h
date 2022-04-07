// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "ConfirmDialogue.h"
#include "Widgets/WSModernTextField.h"

#include "CreateSaveDialogue.generated.h"

class UEditableTextBox;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSaveResponse, bool, Result, FString, SlotName);

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UCreateSaveDialogue : public UConfirmDialogue
{
	GENERATED_BODY()

public:
	FSaveResponse OnSaveResponse;

protected:
	UPROPERTY(meta=(BindWidget))
	UWidgetStudioModernTextField* SaveSlotNameTextBox;

	virtual void NativeOnInitialized() override;
	virtual void Cancel(UWidgetStudioButtonBase* CallingButton) override;
	virtual void Confirm(UWidgetStudioButtonBase* CallingButton) override;

private:
	UFUNCTION()
	bool SaveEnabled();

	UFUNCTION()
	void SaveSlotNameCommit(const FText& Text, ETextCommit::Type CommitMethod);
};
