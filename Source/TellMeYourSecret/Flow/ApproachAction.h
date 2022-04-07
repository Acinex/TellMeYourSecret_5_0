#pragma once
#include "Navigation/PathFollowingComponent.h"
#include "ApproachAction.generated.h"

class UNonPlayerComponent;
class AAIController;
class AStatefulInteractiveObject;
class UApproachComponent;

DECLARE_MULTICAST_DELEGATE(FComplete);

UCLASS()
class UApproachAction : public UObject
{
	GENERATED_BODY()
public:
	bool Approach(AActor* Actor, TWeakObjectPtr<AAIController> InController, TWeakObjectPtr<UNonPlayerComponent> InNonPlayerComponent);

	FComplete OnComplete;

	TWeakObjectPtr<UApproachComponent> GetApproach() const;

private:
	UPROPERTY()
	TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent;
	UPROPERTY()
	TWeakObjectPtr<AAIController> Controller;
	UPROPERTY()
	TWeakObjectPtr<UApproachComponent> ValidApproach;

	FPathFollowingRequestResult PathFollowingRequestResult;

	bool WalkTo(TArray<UApproachComponent*> Approaches);

	void RequestMove();

	UFUNCTION()
	void MovementCompleted(FAIRequestID ID, EPathFollowingResult::Type Result);
};
