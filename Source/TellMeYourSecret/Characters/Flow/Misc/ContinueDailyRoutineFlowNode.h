// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "ContinueDailyRoutineFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Resume Daily Routine"))
class TELLMEYOURSECRET_API UContinueDailyRoutineFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()
public:
	explicit UContinueDailyRoutineFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;
};
