// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"

#include "ChangeReputationFlowNode.generated.h"

UCLASS(NotBlueprintable, meta=(DisplayName="Change reputation"))
class TELLMEYOURSECRET_API UChangeReputationFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()
public:

	UChangeReputationFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif

protected:
	/* Either negative or positive. will be <b>added</b> to the current reputation */
	UPROPERTY(EditAnywhere)
	int8 ReputationChange;
};
