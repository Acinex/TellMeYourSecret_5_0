// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "NonPlayerComponentFlowNode.h"
#include "Navigation/PathFollowingComponent.h"

#include "MoveToFlowNode.generated.h"

#if WITH_EDITOR
enum EMoveToFlowNodeState
{
	None,
	Moving
};
#endif

class AAIController;

UCLASS(NotBlueprintable, meta=(DisplayName="Move to"))
class TELLMEYOURSECRET_API UMoveToFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()
public:
	explicit UMoveToFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	void     RequestMove(APawn* Pawn, FVector& Target);

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual FString GetStatusString() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category = "Target", meta=(DisplayName=Identity))
	FGameplayTagContainer TargetIdentityTags;

	UPROPERTY(EditAnywhere, Category = "Target", meta=(DisplayName=POI))
	FGameplayTagContainer PointOfInterestIdentityTags;

	UPROPERTY(EditAnywhere, Category = "Target", meta=(DisplayName=Location))
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AcceptanceRadius;

	UPROPERTY(EditAnywhere, Category=Movement)
	bool bTryAgainOnFail = true;

	UFUNCTION()
	void MovementCompleted(FAIRequestID ID, EPathFollowingResult::Type Result);

private:
	FPathFollowingRequestResult PathFollowingRequestResult;
	UPROPERTY()
	AAIController* Controller;

	int8 FailCount;

#if WITH_EDITOR
	EMoveToFlowNodeState State = None;
#endif
};
