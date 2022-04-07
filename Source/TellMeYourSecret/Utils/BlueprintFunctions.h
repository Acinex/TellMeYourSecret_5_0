#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Utils/CoreBlueprintFunctions.h"
#include "BlueprintFunctions.generated.h"

class UTellMeYourSecretGameInstance;

UCLASS(BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API UBlueprintFunctions : public UCoreBlueprintFunctions
{
    GENERATED_BODY()
public:
    /**
     * Trying to get a reference to the game instance
     * Can be used from any object which is not inside the world
     */
    UFUNCTION(BlueprintPure, Category = CPPImport)
    static UTellMeYourSecretGameInstance* TryGetGameInstance();

	UFUNCTION(BlueprintPure, Category=CCPImport, meta=(DefaultToSelf))
	static TArray<FString> GetStreamingLevels(const ALevelScriptActor* Level);
};
