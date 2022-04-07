// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "RunnableInterface.h"
#include "UObject/Object.h"
#include "Runnable.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TELLMEYOURSECRET_API URunnable : public UObject, public IRunnableInterface
{
	GENERATED_BODY()

	virtual void Run_Implementation() override;

	virtual UWorld* GetWorld() const override;
};
