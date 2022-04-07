// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "StartRootFlow.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Start RootFlow"))
class TELLMEYOURSECRET_API UStartRootFlow : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()
	public:
	explicit UStartRootFlow(const FObjectInitializer& ObjectInitializer =FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;
};
