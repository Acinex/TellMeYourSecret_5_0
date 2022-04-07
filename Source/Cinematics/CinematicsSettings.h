// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CinematicsSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Cinematics"))
class CINEMATICS_API UCinematicsSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static UCinematicsSettings* Get() { return CastChecked<UCinematicsSettings>(StaticClass()->GetDefaultObject()); }

	UPROPERTY(Config, EditAnywhere, Category = "Preload")
	TArray<FName> Textures;
};
