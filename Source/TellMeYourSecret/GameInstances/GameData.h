#pragma once
#include "Engine/DataAsset.h"
#include "TellMeYourSecret/VolumeType.h"
#include "TellMeYourSecret/UMG/LoadingScreen.h"
#include "TellMeYourSecret/UMG/Menu/MainMenu.h"
#include "GameData.generated.h"

class UUIBase;

UCLASS(BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API UGameData : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundMix* SoundMix;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TMap<EVolumeType, USoundClass*> SoundClasses;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UMainMenu> PauseMenuWidgetClass;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UUIBase> BaseUIWidgetClass;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<ULoadingScreen> LoadingScreenClass;
};
