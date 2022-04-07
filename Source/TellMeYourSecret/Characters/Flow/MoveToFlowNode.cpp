// Copyright Acinex Games 2020

#include "MoveToFlowNode.h"

#include "AIController.h"
#include "FlowSubsystem.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/POI/PoIManager.h"

UMoveToFlowNode::UMoveToFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif

	OutputPins.Add(TEXT("Failed"));
	OutputPins.Add(TEXT("Complete"));
}

void UMoveToFlowNode::RequestMove(APawn* Pawn, FVector& Target)
{
	FAIMoveRequest MoveReq;
	MoveReq.SetNavigationFilter(Controller->GetDefaultNavigationFilterClass());
	MoveReq.SetAcceptanceRadius(AcceptanceRadius);
	Target = TargetLocation;
	UE_LOG(LogTemp, Warning, TEXT("Request Move"));

	if (PointOfInterestIdentityTags.IsValid())
	{
		UPoIManager* PoIManager = UGameplayStatics::GetGameInstance(Controller)->GetSubsystem<UPoIManager>();
		const FVector RandomSpot = PoIManager->FindRandomSpotForActor(PointOfInterestIdentityTags, Pawn);
		Target = RandomSpot;
		MoveReq.SetGoalLocation(RandomSpot);
		if (Target == FVector::ZeroVector)
		{
			AddStatusReport(FString::Printf(
				TEXT("Point of Interest %s does not exist"), *GetIdentityTagsDescription(PointOfInterestIdentityTags)));
		}
	}
	else if (TargetIdentityTags.IsValid())
	{
		TArray<TWeakObjectPtr<UFlowComponent>> Components = GetFlowSubsystem()->GetComponents<UFlowComponent>(
			TargetIdentityTags, EGameplayContainerMatchType::All).Array();
		if (Components.Num())
		{
			MoveReq.SetGoalActor(Components[Components.Num() - 1]->GetOwner());
			Target = MoveReq.GetGoalActor()->GetActorLocation();
		}
		else
		{
			AddStatusReport(
				FString::Printf(TEXT("No Actor for %s found"), *GetIdentityTagsDescription(TargetIdentityTags)));
		}
	}
	else
	{
		MoveReq.SetGoalLocation(TargetLocation);
	}

	PathFollowingRequestResult = Controller->MoveTo(MoveReq);
}

void UMoveToFlowNode::ExecuteInput(const FName& PinName)
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();

	if (!NonPlayerComponent.IsValid())
	{
		return Finish();
	}

	APawn* Pawn = Cast<APawn>(NonPlayerComponent->GetOwner());
	if (!IsValid(Pawn))
	{
		return Finish();
	}

	Controller = Cast<AAIController>(Pawn->GetController());
	Controller->ReceiveMoveCompleted.AddDynamic(this, &UMoveToFlowNode::MovementCompleted);

	FVector Target;
	RequestMove(Pawn, Target);

	DrawDebugSphere(GetWorld(), Target, 40, 20, FColor::Blue, true);

	switch (PathFollowingRequestResult)
	{
	case EPathFollowingRequestResult::Failed:
		FailCount++;
		if (bTryAgainOnFail && FailCount < 10)
		{
			RequestMove(Pawn, Target);
		}
		else
		{
			TriggerOutput(TEXT("Failed"), true);
		}
		break;
	case EPathFollowingRequestResult::AlreadyAtGoal:
		TriggerOutput(TEXT("Complete"), true);
		break;
	case EPathFollowingRequestResult::RequestSuccessful:
		TriggerFirstOutput(false);

#if WITH_EDITOR
		State = Moving;
#endif
		break;
	default: ;
	}
}
#if WITH_EDITOR
FString UMoveToFlowNode::GetNodeDescription() const
{
	const FString Description = PointOfInterestIdentityTags.IsValid()
		                            ? GetIdentityTagsDescription(PointOfInterestIdentityTags)
		                            : TargetIdentityTags.IsValid()
		                            ? GetIdentityTagsDescription(TargetIdentityTags)
		                            : TargetLocation.ToString();

	return Super::GetNodeDescription() + LINE_TERMINATOR + Description;
}

FString UMoveToFlowNode::GetStatusString() const
{
	FString Result = Super::GetStatusString();

	if (FailCount > 0)
	{
		Result.Append(LINE_TERMINATOR).Append(TEXT("Fails: ")).Append(FString::FromInt(FailCount));
	}

	switch (State)
	{
	case Moving:
		if (!Result.IsEmpty())
		{
			Result.Append(LINE_TERMINATOR);
		}
		Result.Append(TEXT("Moving"));
	default: return Result;
	}
}
#endif

void UMoveToFlowNode::MovementCompleted(const FAIRequestID ID, EPathFollowingResult::Type Result)
{
	if (PathFollowingRequestResult.MoveId != ID)
	{
		return;
	}

#if WITH_EDITOR
	State = None;
#endif

	Controller->ReceiveMoveCompleted.RemoveAll(this);
	TriggerOutput(TEXT("Complete"), true);
}
