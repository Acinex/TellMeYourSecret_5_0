#pragma once

#include "TellMeYourSecret/Smartphone/PhoneData.h"
#include "UObject/Object.h"
#include "RecentCall.generated.h"

class UCharacterData;
UCLASS(BlueprintType)
class TELLMEYOURSECRET_API URecentCall : public UObject
{
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn="true"))
    UCharacterData* CharacterData;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn="true"))
    FCall Call;
};
