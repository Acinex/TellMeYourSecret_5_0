#pragma once
#include "CoreMinimal.h"
#include "Direction.generated.h"

UENUM(BlueprintType)
enum class EDirection : uint8
{
    Front UMETA(DisplayName = "Open in front"),
    Back UMETA(DisplayName = "Open to back")
};
