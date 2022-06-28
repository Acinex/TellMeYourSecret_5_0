// Copyright Acinex Games 2020


#include "DoorNavLink.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/Actors/Interact/DoorBase.h"
#include "TellMeYourSecret/Characters/Character/CharacterComponent.h"

UDoorNavLink::UDoorNavLink()
{
	SetMoveReachedLink(this, &UDoorNavLink::NotifySmartLinkReached);

	LinkRelativeStart = {50, 70, 0};
	LinkRelativeEnd = {50, -70, 0};
}

void UDoorNavLink::BeginPlay()
{
	Super::BeginPlay();

	Door = Cast<ADoorBase>(GetOwner());
}

void UDoorNavLink::Complete(AActor* Agent)
{
	ResumePathFollowing(Agent);
	if (UCharacterMovementComponent* CharacterMovementComponent = Agent->FindComponentByClass<UCharacterMovementComponent>())
	{
		CharacterMovementComponent->SetMovementMode(MOVE_Walking, 0);
	}
}

void UDoorNavLink::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const bool CheckForClose = !PendingAgents.IsEmpty();

	for (TMap<AActor*, FVector>::TIterator Iterator = PendingAgents.CreateIterator(); Iterator; ++Iterator)
	{
		const FVector ActorLocation = Iterator.Key()->GetActorLocation();

		const float XDifference = abs(ActorLocation.X) - abs(Iterator.Value().X);
		const float YDifference = abs(ActorLocation.Y) - abs(Iterator.Value().Y);
		if (XDifference < 1 && YDifference < 1)
		{
			Iterator.RemoveCurrent();
		}
	}

	if (CheckForClose && PendingAgents.IsEmpty())
	{
		IInteractiveInterface::Execute_AnimateOff(Door, FLatentActionInfo());
	}
}

void UDoorNavLink::ResumePathFollowing(AActor* Agent)
{
	if (Agent)
	{
		UPathFollowingComponent* PathComp = Agent->FindComponentByClass<UPathFollowingComponent>();
		if (!PathComp)
		{
			const APawn* PawnOwner = Cast<APawn>(Agent);
			if (PawnOwner && PawnOwner->GetController())
			{
				PathComp = PawnOwner->GetController()->FindComponentByClass<UPathFollowingComponent>();
			}
		}

		if (PathComp)
		{
			PathComp->FinishUsingCustomLink(this);
		}
	}
}

void UDoorNavLink::NotifySmartLinkReached(UNavLinkCustomComponent* LinkComp, UObject* PathingAgent, const FVector& DestPoint)
{
	if (const UPathFollowingComponent* PathComp = Cast<UPathFollowingComponent>(PathingAgent))
	{
		AActor* PathOwner = PathComp->GetOwner();

		if (const AController* ControllerOwner = Cast<AController>(PathOwner))
		{
			PathOwner = ControllerOwner->GetPawn();
		}

		UE_LOG(LogTellMeYourSecret, Log, TEXT("%s reached SmartLink"), *PathOwner->GetActorLabel())
		OpenDoor(PathOwner, DestPoint);
	}
}

void UDoorNavLink::OpenDoor(AActor* Agent, const FVector& Destination)
{
	if (!Door || Door->GetState())
	{
		if (Door)
			UE_LOG(LogTellMeYourSecret, Log, TEXT("Door %s was already open"), *Door->GetActorLabel())
		else
			UE_LOG(LogTellMeYourSecret, Log, TEXT("This is not the Door you are looking for"))
		return;
	}

	PendingAgents.Emplace(Agent, Destination);

	const UCharacterComponent* CharacterComponent = Agent->FindComponentByClass<UCharacterComponent>();

	UDoorLinkLatentAction* LatentAction = NewObject<UDoorLinkLatentAction>(this);
	LatentAction->Agent = Agent;
	LatentAction->DoorLink = this;

	FLatentActionInfo LatentInfo;
	LatentInfo.UUID = rand();
	LatentInfo.CallbackTarget = LatentAction;
	LatentInfo.ExecutionFunction = TEXT("ContinueMove");
	LatentInfo.Linkage = 0;

	if (Door->Interact(CharacterComponent->IdentityTags, LatentInfo))
	{
		if (UCharacterMovementComponent* CharacterMovementComponent = Agent->FindComponentByClass<UCharacterMovementComponent>())
		{
			CharacterMovementComponent->SetMovementMode(MOVE_None, 0);
		}
	}
	else
	{
		UE_LOG(LogTellMeYourSecret, Log, TEXT("The Door could not been used"))
	}
}

void UDoorLinkLatentAction::ContinueMove()
{
	DoorLink->Complete(Agent);
}
