// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "VolumeType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EVolumeType : uint8
{
    Master,
    Effects,
    Music,
    Environment,
    Voice,
    Menu
};
