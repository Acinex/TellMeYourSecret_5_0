// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "Engine/DeveloperSettings.h"
#include "TellMeYourSecretGameSettings.generated.h"

class UFlowNode;
/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "TMYS"))
class TELLMEYOURSECRET_API UTellMeYourSecretGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	static UTellMeYourSecretGameSettings* Get() { return CastChecked<UTellMeYourSecretGameSettings>(StaticClass()->GetDefaultObject()); }

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UDataTable> MorphTargetTemplates;

};
