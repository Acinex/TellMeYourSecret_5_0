// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/CharacterData.h"
#include "TellMeYourSecret/Characters/CharacterIdentifier.h"
#include "Engine/GameInstance.h"
#include "TellMeYourSecret/Smartphone/SmartphoneData.h"
#include "TellMeYourSecret/Model/Save/SaveGameInfo.h"
#include "TellMeYourSecret/VolumeType.h"

#include "TellMeYourSecretGameInstance.generated.h"

class UMainMenu;
class UUIBase;
class UUserWidget;
class UQuest;
class UGameData;
class ULoadingScreen;
class UTmysSaveGame;
class USettings;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeforeSave, UTmysSaveGame*, SaveGame);

/**
 * 
 */
UCLASS(Blueprintable)
class TELLMEYOURSECRET_API UTellMeYourSecretGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FBeforeSave OnBeforeSave;
	FBeforeSave OnAfterLoad;

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void PushMenu(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PushPrompt(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);

	virtual void BeginDestroy() override;

	void SetLanguage(const FString NewLanguage) const;
	UFUNCTION(BlueprintCallable)
	float GetVolume(const EVolumeType VolumeType) const;
	UFUNCTION(BlueprintCallable)
	void UpdateVolume(const EVolumeType VolumeType, const float Volume) const;

	TArray<FString> GetCultureNames() const;
	USettings* GetSettings() const;

	void AddSaveSlot(FSaveGameInfo& SaveGameInfo) const;
	void RemoveSaveSlot(const FSaveGameInfo SaveGameInfo) const;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BeginPlay();
	UFUNCTION(BlueprintCallable)
	void PauseGame();
	UFUNCTION(BlueprintCallable)
	void UnpauseGame();
	UFUNCTION(BlueprintCallable)
	void TogglePause();
	UFUNCTION(BlueprintPure)
	bool IsPaused() const;

	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

	UFUNCTION(BlueprintImplementableEvent)
	USmartphoneData* GetSmartphoneData();

	UTmysSaveGame* GetGameValues();
	void SetGameValues(UTmysSaveGame* SaveGame);
	void BeforeSave(const FString SlotName) const;

	void StartGame();

	void UpdatePlayerName(FString PlayerName) const;

protected:
	UPROPERTY()
	UUIBase* BaseUiWidget;
	UPROPERTY()
	UMainMenu* MainMenuWidget;
	UPROPERTY()
	ULoadingScreen* LoadingScreen;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTmysSaveGame* GameValues;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UGameData* GameData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USettings* Settings;

	void SaveSettings() const;

private:
	UPROPERTY()
	TMap<ECharacterIdentifier, UCharacterData*> Characters;

	TArray<FCulturePtr> AvailableCultures;

	int32 MaxLevels;
	int32 LevelsLoaded;

	UFUNCTION(BlueprintCallable)
	void LevelLoaded();
};
