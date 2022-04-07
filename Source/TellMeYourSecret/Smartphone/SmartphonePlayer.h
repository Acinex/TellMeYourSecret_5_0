// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SmartphonePlayer.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USmartphonePlayer : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TELLMEYOURSECRET_API ISmartphonePlayer
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void ToggleSmartphone() = 0;

	UFUNCTION()
	virtual void ToggleSmartphoneCamera() = 0;

	UFUNCTION()
	virtual void DeactivateSmartphoneCamera() = 0;
};
