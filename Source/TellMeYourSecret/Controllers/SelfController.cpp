// Copyright Acinex Games 2020

#include "SelfController.h"

#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"

ASelfController::ASelfController()
{
}

void ASelfController::BeginPlay()
{
	Super::BeginPlay();
}

void ASelfController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Menu", IE_Pressed, this, &ASelfController::ShowMenu);
}

void ASelfController::ShowMenu()
{
	UTellMeYourSecretGameInstance* TellMeYourSecretGameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());
	if (TellMeYourSecretGameInstance)
	{
		TellMeYourSecretGameInstance->PauseGame();
	}
}
