#pragma once
#include "TellMeYourSecret/Characters/CharacterIdentifier.h"
#include "ChatMessage.generated.h"

UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UChatMessage : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Message;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECharacterIdentifier Sender;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECharacterIdentifier With;
};
