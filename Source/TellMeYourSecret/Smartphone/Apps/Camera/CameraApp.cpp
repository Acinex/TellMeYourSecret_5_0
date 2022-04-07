#include "CameraApp.h"

#include "TellMeYourSecret/Smartphone/Smartphone.h"

void UCameraApp::NativeConstruct()
{
	Super::NativeConstruct();

	if (!IsValid(Hud))
	{
		Hud = CreateWidget<UCameraHud>(GetOwningPlayer(), HudClass);
	}
	Hud->AddToViewport();

	Smartphone->ToggleCamera();
}

void UCameraApp::NativeDestruct()
{
	if (IsValid(Hud))
	{
		Hud->RemoveFromViewport();
	}

	Smartphone->DeactivateCamera();
}
