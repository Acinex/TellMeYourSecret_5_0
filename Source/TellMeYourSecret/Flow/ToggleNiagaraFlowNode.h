// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Flow/ActorFlowNode.h"
#include "ToggleNiagaraFlowNode.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Toogle Niagara"))
class TELLMEYOURSECRET_API UToggleNiagaraFlowNode final : public UActorFlowNode
{
	GENERATED_BODY()

public:
	explicit UToggleNiagaraFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void ExecuteInput(const FName& PinName) override;
};
