// Copyright Acinex Games 2020

#include "StartRootFlow.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

UStartRootFlow::UStartRootFlow(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Misc");
#endif
}

void UStartRootFlow::ExecuteInput(const FName& PinName)
{
	TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();

	if (!NonPlayerComponent.IsValid())
	{
		return;
	}

	NonPlayerComponent->StartRootFlow();
	TriggerFirstOutput(true);
}
