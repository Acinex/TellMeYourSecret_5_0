// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TellMeYourSecret/Model/Save/SaveGameInfo.h"

#include "SaveManager.generated.h"

class UTellMeYourSecretGameInstance;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSavesUpdated);

class UTmysSaveGame;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API USaveManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FSavesUpdated OnSavesUpdated;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void DeleteGame(FSaveGameInfo SaveGameInfo);
	UFUNCTION(BlueprintCallable)
	void SaveGame(FSaveGameInfo SaveGameInfo);
	UFUNCTION(BlueprintCallable)
	void LoadGame(const FString& SlotName);

protected:
	UPROPERTY()
	UTellMeYourSecretGameInstance* TmysGameInstance;

	void StartGame(UTmysSaveGame* SaveGame);
};