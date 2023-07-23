// Copyright Acinex Games 2020


#include "SettingsMenu.h"

#include "Input/CommonUIInputTypes.h"

void USettingsMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	BackHandle = RegisterUIActionBinding(FBindUIActionArgs(BackInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleBackAction)));
	ApplyHandle = RegisterUIActionBinding(FBindUIActionArgs(ApplyInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleApplyAction)));
}

void USettingsMenu::HandleApplyAction()
{
}
