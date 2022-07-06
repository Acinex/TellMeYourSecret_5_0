#include "ApproachAction.h"

#include "AIController.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "TellMeYourSecret/Actors/Interact/StatefulInteractiveObject.h"
#include "TellMeYourSecret/Components/ApproachComponent.h"

bool UApproachAction::Approach(AActor* Actor, const TWeakObjectPtr<AAIController> InController, const TWeakObjectPtr<UNonPlayerComponent> InNonPlayerComponent)
{
	if (!Actor)
	{
		return false;
	}

	Controller         = InController;
	NonPlayerComponent = InNonPlayerComponent;
	TArray<UApproachComponent*> Approaches;
	Actor->GetComponents<UApproachComponent>(Approaches);

	const TArray<UApproachComponent*> Specific = Approaches.FilterByPredicate([](const UApproachComponent* Component)
	{
		return !Component->IsForAll();
	});

	Approaches.RemoveAll([Specific](const UApproachComponent* Component)
	{
		return Specific.Contains(Component);
	});

	if (!WalkTo(Specific) && !WalkTo(Approaches))
	{
		return false;
	}

	return true;
}

TWeakObjectPtr<UApproachComponent> UApproachAction::GetApproach() const
{
	return ValidApproach;
}

bool UApproachAction::WalkTo(TArray<UApproachComponent*> Approaches)
{
	for (UApproachComponent* Approach : Approaches)
	{
		if (!Approach->IsOccupied() && Approach->IsFor(NonPlayerComponent->IdentityTags))
		{
			ValidApproach = Approach;
			RequestMove();
			return true;
		}
	}

	return false;
}

void UApproachAction::RequestMove()
{
	FAIMoveRequest MoveReq;
	MoveReq.SetNavigationFilter(Controller->GetDefaultNavigationFilterClass());
	MoveReq.SetGoalLocation(ValidApproach->GetComponentLocation());
	MoveReq.SetAcceptanceRadius(0);
	PathFollowingRequestResult = Controller->MoveTo(MoveReq);
	Controller->ReceiveMoveCompleted.AddDynamic(this, &UApproachAction::MovementCompleted);
}

void UApproachAction::MovementCompleted(const FAIRequestID ID, EPathFollowingResult::Type Result)
{
	if (PathFollowingRequestResult.MoveId != ID)
	{
		return;
	}

	Controller->ReceiveMoveCompleted.RemoveAll(this);
	NonPlayerComponent->GetOwner()->SetActorRotation(ValidApproach->GetComponentRotation());
	OnComplete.Broadcast();
}
