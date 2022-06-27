// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "ActorFlowNode.h"
#include "HideUnhideActorFlowNode.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Hide / Unhide Actor"))
class TELLMEYOURSECRET_API UHideUnhideActorFlowNode : public UActorFlowNode
{
	GENERATED_BODY()
public:
	UHideUnhideActorFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

protected:
	UPROPERTY(EditAnywhere)
	bool bHidden;
};
