// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "ActorFlowNode.h"
#include "TellMeYourSecret/Actors/Interact/InteractiveObject.h"
#include "WaitForInteractionFlowNode.generated.h"

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UWaitForInteractionFlowNode : public UActorFlowNode
{
	GENERATED_BODY()

public:
	UWaitForInteractionFlowNode();
	virtual void ExecuteInput(const FName& PinName) override;

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer User;

	virtual void Cleanup() override;

private:
	UFUNCTION()
	void Interacted(AInteractiveObject* Object, const FGameplayTagContainer& Identity);
};
