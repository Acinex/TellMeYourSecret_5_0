// Copyright Acinex Games 2020

#include "TellMeYourSecretGameInstance.h"

#include "FlowSubsystem.h"
#include "GameFramework/Character.h"
#include "GameData.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/VolumeType.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Cinematics/CinematicsModule.h"
#include "TellMeYourSecret/Characters/ReputationSystem.h"
#include "Engine/AssetManager.h"
#include "Engine/LevelStreaming.h"
#include "GameFramework/GameUserSettings.h"
#include "Internationalization/Culture.h"
#include "TellMeYourSecret/GameInstances/TimeManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetInternationalizationLibrary.h"
#include "TellMeYourSecret/Smartphone/Smartphone.h"
#include "TellMeYourSecret/Model/Save/Settings.h"
#include "TellMeYourSecret/Model/Save/TmysSaveGame.h"
#include "TellMeYourSecret/UMG/LoadingScreen.h"
#include "TellMeYourSecret/GameInstances/SaveGameAware.h"

void UTellMeYourSecretGameInstance::Init()
{
	Super::Init();

#if WITH_EDITOR

	ICinematicsModule& LoadingScreenModule = ICinematicsModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(true, 3.0F);

#endif

	UGameUserSettings::GetGameUserSettings()->ApplySettings(false);

	for (FString LocalizedCultureName : FTextLocalizationManager::Get().GetLocalizedCultureNames(ELocalizationLoadFlags::Game))
	{
		FCulturePtr Culture = FInternationalization::Get().GetCulture(LocalizedCultureName);
		AvailableCultures.Add(Culture);
	}

	if (USettings* LoadGameFromSlot = USettings::Get())
	{
		Settings = LoadGameFromSlot;
	}
	else
	{
		Settings = NewObject<USettings>(this);
	}

	if (USmartphone* Smartphone = GetSubsystem<USmartphone>())
	{
		Smartphone->SetSmartphoneData(GetSmartphoneData());
	}
}

void UTellMeYourSecretGameInstance::BeginDestroy()
{
	Super::BeginDestroy();
	SaveSettings();
}

void UTellMeYourSecretGameInstance::SetLanguage(const FString NewLanguage) const
{
	FString Culture;

	for (const FCulturePtr Ref : AvailableCultures)
	{
		if (NewLanguage.Equals(Ref->GetNativeName()))
		{
			Culture = Ref->GetName();
		}
	}

	UKismetInternationalizationLibrary::SetCurrentLocale(Culture, true);
}

float UTellMeYourSecretGameInstance::GetVolume(const EVolumeType VolumeType) const
{
	if (!Settings)
	{
		return 0.0F;
	}

	const float* Volume = Settings->Volumes.Find(VolumeType);

	if (!Volume)
	{
		return 0.0F;
	}

	return *Volume;
}

void UTellMeYourSecretGameInstance::BeginPlay_Implementation()
{
	StartGame();
}

void UTellMeYourSecretGameInstance::PauseGame()
{
	UGameplayStatics::SetGamePaused(this, true);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PauseMenuWidget && GameData->PauseMenuWidgetClass)
	{
		PauseMenuWidget = CreateWidget<UUserWidget>(PlayerController, GameData->PauseMenuWidgetClass);
	}

	if (!PauseMenuWidget)
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("No Pause-Widget created"))
		return;
	}

	PauseMenuWidget->AddToViewport();
	PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);

	const FInputModeGameAndUI Mode;
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = true;
}

void UTellMeYourSecretGameInstance::UnpauseGame()
{
	if (!PauseMenuWidget)
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("No Pause-Widget created"))
		return;
	}

	UGameplayStatics::SetGamePaused(this, false);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PauseMenuWidget->RemoveFromParent();
	const FInputModeGameOnly Mode;
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = false;
}

void UTellMeYourSecretGameInstance::TogglePause()
{
	if (UGameplayStatics::IsGamePaused(this))
	{
		UnpauseGame();
	}
	else
	{
		PauseGame();
	}
}

bool UTellMeYourSecretGameInstance::IsPaused() const
{
	return UGameplayStatics::IsGamePaused(this);
}

void UTellMeYourSecretGameInstance::UpdateVolume(const EVolumeType VolumeType, const float Volume) const
{
	if (!Settings)
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("No Settings present"))
		return;
	}

	Settings->Volumes.Add(VolumeType, Volume);

	if (GameData)
	{
		UGameplayStatics::SetSoundMixClassOverride(this, GameData->SoundMix, *GameData->SoundClasses.Find(VolumeType), Volume, 1.0F, 0.0F);
	}
}

TArray<FString> UTellMeYourSecretGameInstance::GetCultureNames() const
{
	TArray<FString> Names;

	for (const FCulturePtr Culture : AvailableCultures)
	{
		Names.Add(*Culture->GetDisplayName());
	}

	return Names;
}

USettings* UTellMeYourSecretGameInstance::GetSettings() const
{
	return Settings;
}

void UTellMeYourSecretGameInstance::AddSaveSlot(FSaveGameInfo& SaveGameInfo) const
{
	Settings->LastSaveSlot = SaveGameInfo;

	const int Index = Settings->SaveGameInfos.Find(SaveGameInfo);
	if (Index == -1)
	{
		Settings->SaveGameInfos.Add(SaveGameInfo);
	}
	else
	{
		Settings->SaveGameInfos[Index] = SaveGameInfo;
	}
}

void UTellMeYourSecretGameInstance::RemoveSaveSlot(const FSaveGameInfo SaveGameInfo) const
{
	Settings->SaveGameInfos.Remove(SaveGameInfo);

	if (Settings->LastSaveSlot == SaveGameInfo)
	{
		Settings->LastSaveSlot = FSaveGameInfo();
	}
}

UTmysSaveGame* UTellMeYourSecretGameInstance::GetGameValues()
{
	if (!GameValues)
	{
		GameValues = NewObject<UTmysSaveGame>(this);

		for (int i = 0; i < 4; ++i)
		{
			GameValues->GateCode.Append(FString::FromInt(rand() % 10));
		}

		UE_LOG(LogTellMeYourSecret, Log, TEXT("Code is %s"), *GameValues->GateCode)
	}

	return GameValues;
}

void UTellMeYourSecretGameInstance::SetGameValues(UTmysSaveGame* SaveGame)
{
	GameValues = SaveGame;

	for (UGameInstanceSubsystem* const GameInstanceSubsystem : GetSubsystemArray<UGameInstanceSubsystem>())
	{
		if (ISaveGameAware* SaveGameAware = Cast<ISaveGameAware>(GameInstanceSubsystem))
		{
			SaveGameAware->Load(GameValues);
		}
	}

	GetSubsystem<UTimeManager>()->SetTime(GameValues->CurrentTime.ToUnixTimestamp());

	GetSubsystem<UFlowSubsystem>()->OnGameLoaded(GameValues);

	OnAfterLoad.Broadcast(GameValues);
}

void UTellMeYourSecretGameInstance::BeforeSave(const FString SlotName) const
{
	GameValues->SlotName = SlotName;
	GameValues->PlayerLocation = GetFirstLocalPlayerController(GetWorld())->GetCharacter()->GetTransform();
	GetSubsystem<UFlowSubsystem>()->OnGameSaved(GameValues);

	for (UGameInstanceSubsystem* GameInstanceSubsystem : GetSubsystemArray<UGameInstanceSubsystem>())
	{
		if (ISaveGameAware* SaveGameAware = Cast<ISaveGameAware>(GameInstanceSubsystem))
		{
			SaveGameAware->Save(GameValues);
		}
	}

	OnBeforeSave.Broadcast(GameValues);
}

void UTellMeYourSecretGameInstance::StartGame()
{
	const FInputModeGameOnly Mode;
	GetWorld()->GetFirstPlayerController()->SetInputMode(Mode);
}

void UTellMeYourSecretGameInstance::UpdatePlayerName(FString PlayerName) const
{
	GetSettings()->PlayerName = PlayerName;

	GetSubsystem<UReputationSystem>()->GetCharacter(ECharacterIdentifier::Player)->Name = PlayerName;
}

void UTellMeYourSecretGameInstance::SaveSettings() const
{
	if (Settings)
	{
		Settings->SaveSettings();
	}
}

void UTellMeYourSecretGameInstance::LevelLoaded()
{
	UE_LOG(LogTellMeYourSecret, Warning, TEXT("Progress: %f"), LevelsLoaded *1.0F/ MaxLevels *1.0F)
	LevelsLoaded++;
	LoadingScreen->UpdateLoadingProgress(LevelsLoaded * 1.0F / MaxLevels * 1.0F);
	if (LevelsLoaded == MaxLevels)
	{
		UGameplayStatics::GetGameMode(this)->RestartPlayer(GetWorld()->GetFirstPlayerController());
		// if (LoadingScreen)
		// {
		// 	LoadingScreen->RemoveFromParent();
		// }

		const UFlowSubsystem* FlowSubsystem = GetSubsystem<UFlowSubsystem>();

		TSet<UFlowComponent*> FlowComponents = FlowSubsystem->GetFlowComponentsByTag(FGameplayTag::RequestGameplayTag("World"), UFlowComponent::StaticClass());
		for (UFlowComponent* FlowComponent : FlowComponents)
		{
			FlowComponent->StartRootFlow();
		}

		const FInputModeGameOnly Mode;
		GetWorld()->GetFirstPlayerController()->SetInputMode(Mode);
	}
}
