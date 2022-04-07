#pragma once
#include "Engine/DataAsset.h"
#include "Blueprint/UserWidget.h"
#include "TellMeYourSecret/VolumeType.h"
#include "TellMeYourSecret/UMG/LoadingScreen.h"
#include "GameData.generated.h"


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
    TSubclassOf<UUserWidget> PauseMenuWidgetClass;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<ULoadingScreen> LoadingScreenClass;
};
