// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "OpenCloseEyesFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Open / Close Eyes"))
class TELLMEYOURSECRET_API UOpenCloseEyesFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()
public:
	explicit UOpenCloseEyesFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

protected:
	UPROPERTY(EditAnywhere)
	bool bClose;
};
