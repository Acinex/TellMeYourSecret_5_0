// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RunnableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class URunnableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TELLMEYOURSECRET_API IRunnableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=Runnable)
	void Run();
};
