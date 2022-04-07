#pragma once

#include "CoreMinimal.h"
#include "CoreBlueprintFunctions.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API UCoreBlueprintFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	public:
	UFUNCTION(BlueprintPure, Category = CPPImport)
    static FName GetStreamingLevelNameFromActor(AActor* Actor)
	{
		if (Actor != nullptr)
		{
			return Actor->GetLevel()->GetOuter()->GetFName();
		}

		return NAME_None;
	}

	/**
	* Trying to get a reference to the world
	* Can be used from any object which is not inside the world
	*/
	UFUNCTION(BlueprintPure, Category = CPPImport)
    static UWorld* TryGetWorld();
};
