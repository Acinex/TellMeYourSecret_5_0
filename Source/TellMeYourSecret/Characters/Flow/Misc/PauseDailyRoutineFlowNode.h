// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "PauseDailyRoutineFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Pause Daily Routine"))
class TELLMEYOURSECRET_API UPauseDailyRoutineFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()

public:
	explicit UPauseDailyRoutineFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;
};
