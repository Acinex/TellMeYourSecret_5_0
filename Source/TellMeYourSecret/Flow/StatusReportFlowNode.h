// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Nodes/FlowNode.h"
#include "StatusReportFlowNode.generated.h"

class UTellMeYourSecretGameSettings;
/**
 * 
 */
UCLASS(NotBlueprintable, Abstract)
class TELLMEYOURSECRET_API UStatusReportFlowNode : public UFlowNode
{
	GENERATED_BODY()
public:
	explicit UStatusReportFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR
	virtual bool GetDynamicTitleColor(FLinearColor& OutColor) const override;
	virtual FString GetStatusString() const override;

	virtual bool IsParametersValid() const { return true; }
#endif

protected:
	void AddStatusReport(const FString Message);

	void ClearStatusReport();

#if WITH_EDITOR
private:
	TArray<FString> Log;
#endif
};
