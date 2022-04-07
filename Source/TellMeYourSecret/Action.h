// Copyright Acinex Games 2020.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Runtime\Engine\Classes\Engine\TriggerBase.h>
#include "Action.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class TELLMEYOURSECRET_API UAction : public UObject
{
	GENERATED_BODY()

public:
	UAction();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		ATriggerBase* room;

	UFUNCTION()
		bool canExecute();
};
