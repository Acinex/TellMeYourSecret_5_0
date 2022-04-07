#pragma once

#include "CoreMinimal.h"
#include "Serialization/BufferArchive.h"
#include "InteractiveObjectData.generated.h"


USTRUCT(BlueprintType)
struct TELLMEYOURSECRET_API FInteractiveObjectData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(SaveGame)
	FString Name;

	UPROPERTY(SaveGame)
	TArray<uint8> Data;

	bool operator==(const FInteractiveObjectData& Other) const
	{
		return Other.Name == Name;
	}

	friend FArchive& operator<<(FArchive& Ar, FInteractiveObjectData& InComponentData)
	{
		return Ar;
	}
};
