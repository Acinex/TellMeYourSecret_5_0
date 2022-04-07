// Copyright Acinex Games 2020


#include "ToggleNiagaraFlowNode.h"

#include "TellMeYourSecret/Components/ToggleNiagaraComponent.h"

UToggleNiagaraFlowNode::UToggleNiagaraFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	InputPins.Empty();
	InputPins.Add({TEXT("On"), TEXT("Turns the Emitters on")});
	InputPins.Add({TEXT("Off"), TEXT("Turns the Emitters off")});
}

void UToggleNiagaraFlowNode::ExecuteInput(const FName& PinName)
{
	AActor* Actor = FindActor();
	if (!Actor)
	{
		return;
	}

	TArray<UToggleNiagaraComponent*> Components;
	Actor->GetComponents<UToggleNiagaraComponent>(Components);

	for (UToggleNiagaraComponent* Component : Components)
	{
		if (PinName == TEXT("On"))
		{
			Component->TurnOn();
		}
		else
		{
			Component->TurnOff();
		}
	}

	TriggerFirstOutput(true);
}
