#pragma once

#include "SaveGameInfo.generated.h"

USTRUCT(BlueprintType)
struct FSaveGameInfo
{
	GENERATED_BODY()

	FSaveGameInfo()
	{
	}

	FSaveGameInfo(const FString InSlotName, const FDateTime InDate, const int32 InDay):
		SlotName(InSlotName), Date(InDate), Day(InDay)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString SlotName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDateTime Date;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Day = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString NativeSlotName;

	bool operator==(const FSaveGameInfo& Other) const { return Other.NativeSlotName == NativeSlotName; }
};
