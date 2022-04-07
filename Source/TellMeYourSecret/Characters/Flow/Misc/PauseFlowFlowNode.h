// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "PauseFlowFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Pause Flow"))
class TELLMEYOURSECRET_API UPauseFlowFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()
public:
	explicit UPauseFlowFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;
};
