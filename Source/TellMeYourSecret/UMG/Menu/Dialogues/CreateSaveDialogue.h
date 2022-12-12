// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "ConfirmDialogue.h"
#include "Components/EditableTextBox.h"

#include "CreateSaveDialogue.generated.h"

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
	UEditableTextBox* SaveSlotNameTextBox;

	virtual void NativeOnInitialized() override;
	virtual void Cancel() override;
	virtual void Confirm() override;

private:
	UFUNCTION()
	bool SaveEnabled();

	UFUNCTION()
	void SaveSlotNameCommit(const FText& Text, ETextCommit::Type CommitMethod);
};
