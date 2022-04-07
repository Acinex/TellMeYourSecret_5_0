// Copyright Acinex Games 2020.

#include "TellMeYourSecret.h"

#include "Modules/ModuleManager.h"
#include "Slate/Style/MenuStyles.h"
#include "Styling/SlateStyleRegistry.h"

void FTellMeYourSecretGameModule::StartupModule()
{
	//Hot reload hack
	FSlateStyleRegistry::UnRegisterSlateStyle(FMenuStyles::GetStyleSetName());
	FCoreStyle::Get();
	FMenuStyles::Initialize();
}

void FTellMeYourSecretGameModule::ShutdownModule()
{
	FMenuStyles::Shutdown();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FTellMeYourSecretGameModule, TellMeYourSecret, "TellMeYourSecret");
