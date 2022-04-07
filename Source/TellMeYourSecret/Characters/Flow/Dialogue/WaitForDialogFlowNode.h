// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Nodes/World/FlowNode_ComponentObserver.h"
#include "WaitForDialogFlowNode.generated.h"

UCLASS(NotBlueprintable, meta=(DisplayName="Wait for dialogue", HideCategories="ObservedComponent"))
class TELLMEYOURSECRET_API UWaitForDialogFlowNode : public UFlowNode_ComponentObserver
{
	GENERATED_BODY()

public:
	explicit UWaitForDialogFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	virtual void ObserveActor(TWeakObjectPtr<AActor> Actor, TWeakObjectPtr<UFlowComponent> Component) override;
	virtual void ForgetActor(TWeakObjectPtr<AActor> Actor, TWeakObjectPtr<UFlowComponent> Component) override;
};
