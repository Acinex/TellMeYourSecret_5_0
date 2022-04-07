// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "SaveGameAware.generated.h"

class UTmysSaveGame;

// This class does not need to be modified.
UINTERFACE()
class TELLMEYOURSECRET_API USaveGameAware : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TELLMEYOURSECRET_API ISaveGameAware
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void Load(UTmysSaveGame* SaveGame) = 0;

	UFUNCTION()
	virtual void Save(UTmysSaveGame* SaveGame) = 0;
};
