#pragma once

#include "TimedFlow.generated.h"

USTRUCT(BlueprintType)
struct FTimedFlow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(FlowInput, FlowOutput))
	int32 Hour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(FlowInput, FlowOutput))
	int32 Minute;
};
