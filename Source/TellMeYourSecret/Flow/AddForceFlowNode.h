// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "ActorFlowNode.h"
#include "AddForceFlowNode.generated.h"

UCLASS(meta=(DisplayName="Add Force"))
class TELLMEYOURSECRET_API UAddForceFlowNode : public UActorFlowNode
{
	GENERATED_BODY()

public:
	explicit UAddForceFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

protected:
	/** Force vector to apply. Magnitude indicates strength of force. */
	UPROPERTY(EditAnywhere)
	FVector Force;
	/** If a SkeletalMeshComponent, name of body to apply force to. 'None' indicates root body. */
	UPROPERTY(EditAnywhere)
	FName BoneName;
	/** If true, Force is taken as a change in acceleration instead of a physical force (i.e. mass will have no effect). */
	UPROPERTY(EditAnywhere)
	bool bAccelChange;
};
