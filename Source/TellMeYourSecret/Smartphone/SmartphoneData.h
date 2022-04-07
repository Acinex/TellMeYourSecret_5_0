// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SmartphoneData.generated.h"

class UCameraApp;
class UQuestApp;
class UTalkApp;
class UContactApp;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API USmartphoneData : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundBase* NotificationSound;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FSlateBrush NotificationImage;
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UContactApp> ContactAppClass;
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UTalkApp> TalkAppClass;
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UQuestApp> QuestAppClass;
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UCameraApp> CameraAppClass;
};
