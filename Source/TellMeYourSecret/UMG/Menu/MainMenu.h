// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "TellMeYourSecret/UMG/TMYSButton.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UMainMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UTMYSButton* PlayButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UTMYSButton* GameButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UTMYSButton* CustomizationButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UTMYSButton* OptionsButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UTMYSButton* AboutButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UTMYSButton* QuitButton;

	virtual void NativeOnActivated() override;
	virtual void NativeOnInitialized() override;

	virtual bool NativeOnHandleBackAction() override;
	
	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	
	UFUNCTION(BlueprintImplementableEvent)
	void ShowGame();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowCustomization();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowOptions();
	UFUNCTION(BlueprintImplementableEvent)
	void ShowAbout();
	
private:

	UFUNCTION()
	void Play();
	UFUNCTION()
	void Quit();
};
