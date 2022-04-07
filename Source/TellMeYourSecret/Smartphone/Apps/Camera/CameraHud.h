// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "CameraHud.generated.h"

class UButton;
class USmartphone;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UCameraHud : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* SwitchCameraButton;
	UPROPERTY(meta=(BindWidget))
	UButton* TakePhotoButton;
	UPROPERTY(meta=(BindWidget))
	UButton* BackButton;

private:
	UPROPERTY()
	USmartphone* Smartphone;

	UFUNCTION()
	void SwitchCameraButtonClicked();
	UFUNCTION()
	void TakePhotoButtonClicked();
	UFUNCTION()
	void BackButtonClicked();
};
