#pragma once

#include "CoreMinimal.h"

#include "CharacterIdentifier.h"

#include "CharacterStruct.generated.h"

USTRUCT(BlueprintType)
struct TELLMEYOURSECRET_API FCharacterStruct
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    ECharacterIdentifier ID;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FString Name;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FString OfficialName;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FSlateBrush Image;
};
