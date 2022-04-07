// Copyright Acinex Games 2020


#include "Runnable.h"

#include "TellMeYourSecret/Utils/CoreBlueprintFunctions.h"

void URunnable::Run_Implementation()
{
	IRunnableInterface::Run_Implementation();
}

UWorld* URunnable::GetWorld() const
{
	return UCoreBlueprintFunctions::TryGetWorld();
}
