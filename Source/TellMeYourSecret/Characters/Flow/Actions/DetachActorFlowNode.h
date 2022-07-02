// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "TellMeYourSecret/Flow/ActorFlowNode.h"
#include "DetachActorFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Detach Actor"))
class TELLMEYOURSECRET_API UDetachActorFlowNode : public UActorFlowNode
{
	GENERATED_BODY()
	explicit UDetachActorFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Item")
	FGameplayTagContainer ItemIdentityTags;
	UPROPERTY(EditAnywhere)
	bool bSimulatePhysics = true;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif
};
