// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Nodes/FlowNode.h"
#include "TellMeYourSecret/Flow/StatusReportFlowNode.h"

#include "LockUnlockObjectFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Lock / Unlock Object"))
class TELLMEYOURSECRET_API ULockUnlockObjectFlowNode : public UStatusReportFlowNode
{
	GENERATED_BODY()

public:
	explicit ULockUnlockObjectFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void ExecuteInput(const FName& PinName) override;

protected:
	/** The InteractiveObject which lock state should be changed */
	UPROPERTY(EditAnywhere, Category = Lock)
	FGameplayTagContainer InteractionIdentityTags;
	/** Actor the lock should be changed for */
	UPROPERTY(EditAnywhere, Category = Lock)
	FGameplayTagContainer IdentityTags;

	UPROPERTY(EditAnywhere, Category=Lock)
	bool bLock;
};
