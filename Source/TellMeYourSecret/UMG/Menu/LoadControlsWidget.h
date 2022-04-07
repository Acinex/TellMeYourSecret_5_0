// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "LoadControlsWidget.generated.h"

class UPanelWidget;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API ULoadControlsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	explicit ULoadControlsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* GameSlots;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SaveGameWidgetClass;

	UFUNCTION()
	void Reload();

};
