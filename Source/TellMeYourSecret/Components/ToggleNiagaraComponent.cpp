// Copyright Acinex Games 2020

#include "ToggleNiagaraComponent.h"
#include "Niagara/Public/NiagaraComponent.h"

UToggleNiagaraComponent::UToggleNiagaraComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UToggleNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UToggleNiagaraComponent::TurnOn() const
{
	TArray<UNiagaraComponent*> Components;
	GetOwner()->GetComponents<UNiagaraComponent>(Components);

	for (UNiagaraComponent* NiagaraComponent : Components)
	{
		NiagaraComponent->Activate();
	}
}

void UToggleNiagaraComponent::TurnOff() const
{
	TArray<UNiagaraComponent*> Components;
	GetOwner()->GetComponents<UNiagaraComponent>(Components);

	for (UNiagaraComponent* NiagaraComponent : Components)
	{
		NiagaraComponent->Deactivate();
	}
}
