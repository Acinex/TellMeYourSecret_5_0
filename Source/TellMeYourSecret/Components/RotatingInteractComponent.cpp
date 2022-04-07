// Copyright Acinex Games 2020

#include "RotatingInteractComponent.h"

#include "DelayAction.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"
#include "TellMeYourSecret/Model/Util/ActorUtil.h"

const FName URotatingInteractComponent::Wanted_Tag = FName("Rotate");

URotatingInteractComponent::URotatingInteractComponent()
{
	TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	TimelineFloat.BindUFunction(this, FName("TimelineUpdate"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));
}

void URotatingInteractComponent::AnimateOn_Implementation(FLatentActionInfo LatentInfo)
{
	if (!TimeLine)
	{
		return;
	}

	if (TimeLine->GetPlaybackPosition() <= 0.01F)
	{
		PlaySound(OpenSound);
	}

	FLatentActionManager& LatentActionManager = GetWorld()->GetLatentActionManager();

	if (LatentActionManager.FindExistingAction<FDelayAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == nullptr)
	{
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FDelayAction(TimeLine->GetTimelineLength(), LatentInfo));
	}

	TimeLine->Play();
}

void URotatingInteractComponent::AnimateOff_Implementation(FLatentActionInfo LatentInfo)
{
	if (!TimeLine)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = GetWorld()->GetLatentActionManager();

	if (LatentActionManager.FindExistingAction<FDelayAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == nullptr)
	{
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FDelayAction(TimeLine->GetPlaybackPosition(), LatentInfo));
	}

	TimeLine->Reverse();
}

void URotatingInteractComponent::TurnOn_Implementation()
{
	Super::TurnOn_Implementation();
	TimelineUpdate(1.0F);

	if (TimeLine)
	{
		TimeLine->SetNewTime(TimeLine->GetTimelineLength());
	}
}

void URotatingInteractComponent::TurnOff_Implementation()
{
	Super::TurnOff_Implementation();
	TimelineUpdate(0.0F);

	if (TimeLine)
	{
		TimeLine->SetNewTime(0);
	}
}

void URotatingInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	if (TimeLine && AnimationCurve)
	{
		TimeLine->AddInterpFloat(AnimationCurve, TimelineFloat, FName("Alpha"));
		TimeLine->SetTimelineFinishedFunc(TimelineFinished);
		TimeLine->SetLooping(false);
	}
}

void URotatingInteractComponent::TimelineUpdate(const float Value)
{
	TArray<USceneComponent*> Doors = GetTaggedComponents<USceneComponent>();

	if (!Doors.Num())
	{
		return;
	}

	float Amount = FMath::Lerp(0.0F, Degrees, Value);

	if (Direction == EDirection::Front)
	{
		Amount *= -1;
	}

	for (USceneComponent* Element : Doors)
	{
		FActorUtil::Rotate(Element, Amount, EAxis::Z);
	}
}

void URotatingInteractComponent::OnTimelineFinished()
{
	if (!TimeLine->IsReversing())
	{
		return;
	}

	PlaySound(CloseSound);
}

void URotatingInteractComponent::PlaySound(USoundBase* Sound) const
{
	if (!Sound)
	{
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(this, Sound, GetOwner()->GetActorLocation());
}
