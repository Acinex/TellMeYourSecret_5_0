// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UObject/Object.h"
#include "SettingsMenu.generated.h"

/**
 * 
 */
UCLASS(Abstract, meta = (Category = "Settings", DisableNativeTick))
class TELLMEYOURSECRET_API USettingsMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle BackInputActionData;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle ApplyInputActionData;

private:
	FUIActionBindingHandle BackHandle;
	FUIActionBindingHandle ApplyHandle;

	
	void HandleApplyAction();
};
