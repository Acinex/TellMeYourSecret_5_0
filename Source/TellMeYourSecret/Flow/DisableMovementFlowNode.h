// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Flow/ActorFlowNode.h"
#include "DisableMovementFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Enable / Disble Movement"))
class TELLMEYOURSECRET_API UDisableMovementFlowNode : public UActorFlowNode
{
	GENERATED_BODY()

public:
	explicit UDisableMovementFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void ExecuteInput(const FName& PinName) override;

protected:
	UPROPERTY(EditAnywhere)
	bool bEnable;
};
