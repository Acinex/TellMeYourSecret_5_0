#pragma once
#include "CameraHud.h"
#include "TellMeYourSecret/Smartphone/Apps/AppWidget.h"

#include "CameraApp.generated.h"

UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UCameraApp : public UAppWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual int GetRow() const override { return 1; }
	virtual int GetColumn() const override { return 1; }

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraHud> HudClass;

private:
	UPROPERTY()
	UCameraHud* Hud;
};
