#pragma once

#include "CoreMinimal.h"
#include "Syllable.generated.h"

USTRUCT(meta=(TitleProperty="Syllable"))
struct FSyllable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Syllable;

	UPROPERTY(EditAnywhere)
	float Duration = 0.05F;

	FSyllable()
	{
	}

	explicit FSyllable(const FString InSyllable): Syllable(InSyllable)
	{
	}
};
