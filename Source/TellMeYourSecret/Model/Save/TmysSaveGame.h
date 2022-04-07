// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FlowSave.h"
#include "TellMeYourSecret/Smartphone/PhoneData.h"
#include "TellMeYourSecret/GameInstances/InteractiveObjectData.h"

#include "TmysSaveGame.generated.h"

class AStatefulInteractiveObject;
class UQuest;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UTmysSaveGame : public UFlowSaveGame
{
	GENERATED_BODY()

public:
	UTmysSaveGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	bool bNew;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FString SlotName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame)
	FString PlayerName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FDateTime CurrentTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FTransform PlayerLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FName Map;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	TArray<FInteractiveObjectData> InteractiveObjects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FString GateCode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FPhoneData PhoneData;
	virtual FPhoneData GetPhoneData();
	virtual void SetPhoneData(FPhoneData& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	TSet<ECharacterIdentifier> KnownCharacters;
	virtual TSet<ECharacterIdentifier> GetKnownCharacters();
	virtual void SetKnownCharacters(TSet<ECharacterIdentifier> Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	TMap<ECharacterIdentifier, int32> Reputations;
	virtual TMap<ECharacterIdentifier, int32> GetReputations();
	virtual void SetReputations(TMap<ECharacterIdentifier, int32> Value);
};
