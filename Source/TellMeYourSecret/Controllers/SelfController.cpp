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
	InputComponent->BindAction("Menu", IE_Pressed, this, &ASelfController::ShowMenu);
}

void ASelfController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTellMeYourSecret, Log, TEXT("Pawn is: %s"), *InPawn->GetClass()->GetName())
}

void ASelfController::ShowMenu()
{
	UTellMeYourSecretGameInstance* TellMeYourSecretGameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());
	if (TellMeYourSecretGameInstance)
	{
		TellMeYourSecretGameInstance->PauseGame();
	}
}
