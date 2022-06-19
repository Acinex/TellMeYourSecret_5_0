// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "StatusReportFlowNode.h"
#include "WaitForTimeFlowNode.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Wait for Time"))
class TELLMEYOURSECRET_API UWaitForTimeFlowNode : public UStatusReportFlowNode
{
	GENERATED_BODY()
public:
	explicit UWaitForTimeFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void ExecuteInput(const FName& PinName) override;
protected:
	UPROPERTY(EditAnywhere)
	int32 Hour;
	UPROPERTY(EditAnywhere)
	int32 Minute;

	virtual void Cleanup() override;
private:
	UFUNCTION()
	void TimeChanged(int32 CurrentHour, int32 CurrentMinute);
};
