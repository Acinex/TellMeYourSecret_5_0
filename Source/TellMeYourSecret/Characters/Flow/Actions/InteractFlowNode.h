// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "ApproachAction.h"
#include "Navigation/PathFollowingComponent.h"
#include "TellMeYourSecret/Characters/Flow/Animations/AbstractMontageFlowNode.h"

#include "InteractFlowNode.generated.h"

class AInteractiveObject;
class AAIController;
class UApproachAction;
/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Interact"))
class TELLMEYOURSECRET_API UInteractFlowNode : public UAbstractMontageFlowNode
{
	GENERATED_BODY()

public:
	explicit UInteractFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	FGameplayTagContainer InteractionIdentityTags;

	virtual void OnAnimNotify(const FName Name) override;

	virtual void OnComplete() override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif

private:
	UPROPERTY()
	AInteractiveObject* InteractiveObject;

	UPROPERTY()
	UApproachAction* ApproachAction;

	UPROPERTY()
	TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent;
	UPROPERTY()
	TWeakObjectPtr<AAIController> Controller;
	UPROPERTY()
	TWeakObjectPtr<UApproachComponent> ValidApproach;

	FPathFollowingRequestResult PathFollowingRequestResult;
};
