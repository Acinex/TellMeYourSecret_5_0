#pragma once
#include "SaveGameInfo.h"
#include "GameFramework/SaveGame.h"
#include "TellMeYourSecret/VolumeType.h"

#include "Settings.generated.h"

UCLASS()
class TELLMEYOURSECRET_API USettings : public USaveGame
{
	GENERATED_BODY()

public:
	static const FString SlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FSaveGameInfo LastSaveSlot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	TArray<FSaveGameInfo> SaveGameInfos;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FString Language;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FString PlayerName = TEXT("John");
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	TMap<EVolumeType, float> Volumes{
		{EVolumeType::Effects, 0.5F},
		{EVolumeType::Environment, 0.5F},
		{EVolumeType::Master, 0.5F},
		{EVolumeType::Menu, 0.5F},
		{EVolumeType::Music, 0.1F},
		{EVolumeType::Voice, 0.5F}
	};
};
