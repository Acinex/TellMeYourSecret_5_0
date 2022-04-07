#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "NumericRelation.generated.h"


UENUM(BlueprintType)
enum class ENumericRelation : uint8
{
    Greater_Than UMETA(DisplayName="Greater than"),
    Lower_Than UMETA(DisplayName="Lower than"),
    Equal UMETA(DisplayName="Equal"),
    Greater_Than_Equal UMETA(DisplayName="Greater than Equal"),
    Lower_Than_Equal UMETA(DisplayName="Lower than Equal")
};

class TELLMEYOURSECRET_API FNumericRelationUtil
{
public:
    static bool Check(const ENumericRelation NumericRelation, int32 Actual, int32 Expected);
};
