// Copyright Acinex Games 2020

#include "DoorLink.h"

#include "NavLinkCustomComponent.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interact/DoorBase.h"
#include "TellMeYourSecret/Log.h"

static FString ActiveName;

void UDoorLinkLatentAction::ContinueMove()
{
	DoorLink->Complete(Agent);
}

ADoorLink::ADoorLink(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	OnSmartLinkReached.AddDynamic(this, &ADoorLink::OpenDoor);
	PointLinks.Empty();
	bSmartLinkIsRelevant = true;

	PrimaryActorTick.bCanEverTick          = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.SetTickFunctionEnable(true);

	GetSmartLinkComp()->SetLinkData({0, -50, 0}, {0, 50, 0}, ENavLinkDirection::BothWays);
}

void ADoorLink::Complete(AActor* Agent)
{
	ResumePathFollowing(Agent);
	UCharacterMovementComponent* CharacterMovementComponent = Agent->FindComponentByClass<UCharacterMovementComponent>();
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->SetMovementMode(MOVE_Walking, 0);
	}
}

void ADoorLink::OpenDoor(AActor* Agent, const FVector& Destination)
{
	if (!Door || Door->GetState())
	{
		if (Door)
			UE_LOG(LogTellMeYourSecret, Log, TEXT("Door %s was already open"), *Door->GetName())
		else
			UE_LOG(LogTellMeYourSecret, Log, TEXT("This is not the Door you are looking for"))
		return;
	}

	PendingAgents.Emplace(Agent, Destination);
	ActiveName = GetName();

	UCharacterComponent* CharacterComponent = Agent->FindComponentByClass<UCharacterComponent>();

	UDoorLinkLatentAction* LatentAction = NewObject<UDoorLinkLatentAction>(this);
	LatentAction->Agent                 = Agent;
	LatentAction->DoorLink              = this;

	FLatentActionInfo LatentInfo;
	LatentInfo.UUID              = rand();
	LatentInfo.CallbackTarget    = LatentAction;
	LatentInfo.ExecutionFunction = TEXT("ContinueMove");
	LatentInfo.Linkage           = 0;
	if (Door->Interact(CharacterComponent->IdentityTags, LatentInfo))
	{
		UCharacterMovementComponent* CharacterMovementComponent = Agent->FindComponentByClass<UCharacterMovementComponent>();
		if (CharacterMovementComponent)
		{
			CharacterMovementComponent->SetMovementMode(MOVE_None, 0);
		}
	}
}

void ADoorLink::Tick(float DeltaSeconds)
{
	for (TMap<AActor*, FVector>::TIterator Iterator = PendingAgents.CreateIterator(); Iterator; ++Iterator)
	{
		const FVector ActorLocation = Iterator.Key()->GetActorLocation();

		const float XDifference = abs(ActorLocation.X) - abs(Iterator.Value().X);
		const float YDifference = abs(ActorLocation.Y) - abs(Iterator.Value().Y);
		if (XDifference < 1 && YDifference < 1)
		{
			Iterator.RemoveCurrent();
			IInteractiveInterface::Execute_AnimateOff(Door, FLatentActionInfo());
		}
	}
}
