// Copyright Acinex Games 2020.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "RoomType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERoomType : uint8
{
    Bedroom UMETA(DisplayName = "Bedroom"),
    Livingroom UMETA(DisplayName = "Livingroom"),
    Kitchen UMETA(DisplayName = "Kitchen"),
    Bathroom UMETA(DisplayName = "Bathroom")
};
