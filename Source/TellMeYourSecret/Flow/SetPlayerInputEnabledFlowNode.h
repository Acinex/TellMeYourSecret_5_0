// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Nodes/FlowNode.h"
#include "SetPlayerInputEnabledFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Set Player input enabled"))
class TELLMEYOURSECRET_API USetPlayerInputEnabledFlowNode : public UFlowNode
{
	GENERATED_BODY()

public:
	explicit USetPlayerInputEnabledFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif

protected:
	UPROPERTY(EditInstanceOnly)
	bool bEnabled;
};
