// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "StatusReportFlowNode.h"
#include "WaitForTimeFlowNode.generated.h"

class UTimeManager;
/**
 * 
 */
UCLASS(meta=(DisplayName="Wait for Time"))
class TELLMEYOURSECRET_API UWaitForTimeFlowNode : public UFlowNode
{
	GENERATED_BODY()
public:
	explicit UWaitForTimeFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetStatusString() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(FlowInput))
	int32 Hour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(FlowInput))
	int32 Minute;

	virtual void Cleanup() override;
private:
	UFUNCTION()
	void TimeChanged(int32 CurrentHour, int32 CurrentMinute);

	UPROPERTY()
	UTimeManager* TimeManager;
};
