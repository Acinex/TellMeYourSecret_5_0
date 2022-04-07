// Copyright Acinex Games 2020.

#include "TellMeYourSecretGameModeBase.h"

#include "EngineUtils.h"
#include "FlowSubsystem.h"
#include "Cinematics/CinematicsModule.h"
#include "GameFramework/PlayerStart.h"
#include "GameInstances/TellMeYourSecretGameInstance.h"
#include "Model/Save/TmysSaveGame.h"
#include "TellMeYourSecret/Log.h"

ATellMeYourSecretGameModeBase::ATellMeYourSecretGameModeBase()
{
	bStartPlayersAsSpectators = false;
}

void ATellMeYourSecretGameModeBase::BeginPlay()
{
	Super::BeginPlay();

#if WITH_EDITOR
	UTellMeYourSecretGameInstance* TellMeYourSecretGameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());
	if (TellMeYourSecretGameInstance->GetGameValues()->bNew)
	{
		TellMeYourSecretGameInstance->SetGameValues(TellMeYourSecretGameInstance->GetGameValues());
	}
#endif

	
	ICinematicsModule& LoadingScreenModule = ICinematicsModule::Get();
	LoadingScreenModule.StopInGameLoadingScreen();
}

void ATellMeYourSecretGameModeBase::RestartPlayer(AController* NewPlayer)
{
	if (NewPlayer == nullptr || NewPlayer->IsPendingKillPending())
	{
		return;
	}

	UTellMeYourSecretGameInstance* TellMeYourSecretGameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());
	const FTransform PlayerLocation = TellMeYourSecretGameInstance->GetGameValues()->PlayerLocation;

	if (!PlayerLocation.GetLocation().IsZero())
	{
		AActor* Spawn = GetWorld()->SpawnActor(APlayerStart::StaticClass(), &PlayerLocation);

		UE_LOG(LogTellMeYourSecret, Log, TEXT("Player Location: %s"), *PlayerLocation.ToString())
		UE_LOG(LogTellMeYourSecret, Log, TEXT("Spawn Location: %s"), *Spawn->GetActorTransform().ToString())
		RestartPlayerAtPlayerStart(NewPlayer, Spawn);
	}
	else
	{
		RestartPlayerAtPlayerStart(NewPlayer, FindPlayerStart(NewPlayer));
	}
}

void ATellMeYourSecretGameModeBase::StartPlay()
{
	Super::StartPlay();
}
