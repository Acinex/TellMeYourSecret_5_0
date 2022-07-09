// Copyright Acinex Games 2022

#pragma once


#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "WhileFlowNode.generated.h"

/**
 * Can repeat his Do pin until it's stopped with a call to Break 
 */
UCLASS(meta=(DisplayName="Do While"))
class TELLMEYOURSECRET_API UWhileFlowNode : public UFlowNode
{
	GENERATED_BODY()
public:
	explicit UWhileFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

private:
	bool bBreak;
};
