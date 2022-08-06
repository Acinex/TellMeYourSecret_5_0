// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "../StatusReportFlowNode.h"
#include "RandomGameplayTagContainerFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Select Random GameplayTagContainer"))
class TELLMEYOURSECRET_API URandomGameplayTagContainerFlowNode : public UStatusReportFlowNode
{
	GENERATED_BODY()

public:
	explicit URandomGameplayTagContainerFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual bool IsParametersValid() const override;
#endif
	
protected:
	UPROPERTY(EditAnywhere)
	TArray<FGameplayTagContainer> Tags;

	UPROPERTY(BlueprintReadOnly, meta=(FlowOutput))
	FGameplayTagContainer Selected;
};
