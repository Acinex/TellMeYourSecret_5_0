// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerInput.h"

#include "KeyBindingWidget.generated.h"

class UInputKeySelector;
class UTextBlock;
UCLASS()
class UKeyBinding : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FInputActionKeyMapping KeyMapping;

	UPROPERTY()
	FText Label;
};

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UKeyBindingWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Label;
	UPROPERTY(meta=(BindWidget))
	UInputKeySelector* KeySelector;

	UPROPERTY()
	UKeyBinding* KeyBinding;
};
