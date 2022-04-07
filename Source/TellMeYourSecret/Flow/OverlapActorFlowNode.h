// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Nodes/World/FlowNode_ComponentObserver.h"
#include "OverlapActorFlowNode.generated.h"

class UFlowComponent;
/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="On Actor Overlap"))
class TELLMEYOURSECRET_API UOverlapActorFlowNode : public UFlowNode_ComponentObserver
{
	GENERATED_BODY()
public:
	explicit UOverlapActorFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(EditAnywhere, Category = "Trigger")
	FGameplayTag OverlappedActorTag;

	virtual void ExecuteInput(const FName& PinName) override;

	virtual void ObserveActor(TWeakObjectPtr<AActor> Actor, TWeakObjectPtr<UFlowComponent> Component) override;
	virtual void ForgetActor(TWeakObjectPtr<AActor> Actor, TWeakObjectPtr<UFlowComponent> Component) override;

private:
	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
