// Copyright Acinex Games 2020

#include "SaveManager.h"

#include "FlowSubsystem.h"
#include "GameFramework/Character.h"
#include "TellMeYourSecretGameInstance.h"
#include "Cinematics/CinematicsModule.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Model/Save/Settings.h"
#include "TellMeYourSecret/Model/Save/TmysSaveGame.h"
#include "TellMeYourSecret/Log.h"

void USaveManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	TmysGameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());
}

void USaveManager::DeleteGame(FSaveGameInfo SaveGameInfo)
{
	if (UGameplayStatics::DeleteGameInSlot(SaveGameInfo.NativeSlotName, 0))
	{
		TmysGameInstance->RemoveSaveSlot(SaveGameInfo);
		OnSavesUpdated.Broadcast();
	}
}

void USaveManager::SaveGame(FSaveGameInfo SaveGameInfo)
{
	if (!TmysGameInstance->GetGameValues())
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("No Save Game provided"))
		return;
	}

	TmysGameInstance->BeforeSave(SaveGameInfo.SlotName);
	TmysGameInstance->GetGameValues()->bNew = false;

	if (SaveGameInfo.NativeSlotName.IsEmpty())
	{
		SaveGameInfo.NativeSlotName = TEXT("s_") + FString::FromInt(TmysGameInstance->GetSettings()->SaveGameInfos.Num());
	}

	SaveGameInfo.Date = FDateTime::Now();

	if (UGameplayStatics::SaveGameToSlot(TmysGameInstance->GetGameValues(), SaveGameInfo.NativeSlotName, 0))
	{
		TmysGameInstance->AddSaveSlot(SaveGameInfo);
		OnSavesUpdated.Broadcast();
	}
}

void USaveManager::LoadGame(const FString& SlotName)
{
	UGameplayStatics::SetGamePaused(this, false);
	UFlowSubsystem* FlowSubsystem = GetGameInstance()->GetSubsystem<UFlowSubsystem>();
	for (const TTuple<UObject*, UFlowAsset*> RootInstance : FlowSubsystem->GetRootInstances())
	{
		FlowSubsystem->FinishRootFlow(RootInstance.Key, RootInstance.Value, EFlowFinishPolicy::Abort);
	}

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, [this, SlotName]()
	{
		if (SlotName.IsEmpty())
		{
			StartGame(NewObject<UTmysSaveGame>(this));
			return;
		}

		FAsyncLoadGameFromSlotDelegate Delegate;

		Delegate.BindLambda([this](const FString& LoadedSlotName, const int32 Index, USaveGame* SaveGame)
		{
			StartGame(Cast<UTmysSaveGame>(SaveGame));
		});
		UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, Delegate);
	}, 0.2F, false);
}

void USaveManager::StartGame(UTmysSaveGame* SaveGame)
{
	TmysGameInstance->SetGameValues(SaveGame);
	UGameplayStatics::OpenLevel(this, SaveGame->Map);
}
