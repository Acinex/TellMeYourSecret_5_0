// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"

#include "Blueprint/UserWidget.h"
#include "CustomizationMenuContent.generated.h"

class UTellMeYourSecretGameInstance;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UCustomizationMenuContent : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	virtual bool NativeOnHandleBackAction() override;

protected:
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* PlayerNameTextBox;

private:
	UPROPERTY()
	UTellMeYourSecretGameInstance* GameInstance;

	UFUNCTION()
	void PlayerNameChanged(const FText& PlayerName, ETextCommit::Type CommitMethod);
};
