#pragma once
#include "SaveGameInfo.h"
#include "GameFramework/GameUserSettings.h"
#include "TellMeYourSecret/VolumeType.h"

#include "Settings.generated.h"

UCLASS()
class TELLMEYOURSECRET_API USettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	static USettings* Get();

	UPROPERTY(config, VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FSaveGameInfo LastSaveSlot;
	UPROPERTY(config, VisibleAnywhere, BlueprintReadOnly, SaveGame)
	TArray<FSaveGameInfo> SaveGameInfos;
	UPROPERTY(config, VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FString Language;
	UPROPERTY(config, VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FString PlayerName = TEXT("John");
	UPROPERTY(config, VisibleAnywhere, BlueprintReadOnly, SaveGame)
	TMap<EVolumeType, float> Volumes{
		{EVolumeType::Effects, 0.5F},
		{EVolumeType::Environment, 0.5F},
		{EVolumeType::Master, 0.5F},
		{EVolumeType::Menu, 0.5F},
		{EVolumeType::Music, 0.1F},
		{EVolumeType::Voice, 0.5F}
	};
};
