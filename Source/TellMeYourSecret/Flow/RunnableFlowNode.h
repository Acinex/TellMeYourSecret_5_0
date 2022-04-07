// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "StatusReportFlowNode.h"
#include "RunnableFlowNode.generated.h"

class URunnable;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API URunnableFlowNode : public UStatusReportFlowNode
{
	GENERATED_BODY()

	virtual void ExecuteInput(const FName& PinName) override;

protected:
	UPROPERTY(EditInstanceOnly)
	TSubclassOf<URunnable> Class;
};
