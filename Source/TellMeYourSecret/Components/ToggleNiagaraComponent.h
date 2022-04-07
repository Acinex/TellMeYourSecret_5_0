// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "FlowComponent.h"

#include "ToggleNiagaraComponent.generated.h"


UCLASS(ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API UToggleNiagaraComponent final : public UFlowComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UToggleNiagaraComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void TurnOn() const;
	void TurnOff() const;
};
