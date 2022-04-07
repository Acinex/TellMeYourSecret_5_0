// Copyright Acinex Games 2020

#include "SlideInteractComponent.h"

#include "DelayAction.h"
#include "Components/TimelineComponent.h"
#include "TellMeYourSecret/Model/Util/ActorUtil.h"

const FName USlideInteractComponent::Wanted_Tag = FName("Slide");

USlideInteractComponent::USlideInteractComponent()
{
	TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
	TimelineFloat.BindUFunction(this, FName("TimelineUpdate"));
}

void USlideInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	if (TimeLine && AnimationCurve)
	{
		TimeLine->AddInterpFloat(AnimationCurve, TimelineFloat, FName("Alpha"));
		TimeLine->SetLooping(false);
	}
}

void USlideInteractComponent::AnimateOn_Implementation(FLatentActionInfo LatentInfo)
{
	if (!TimeLine)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = GetWorld()->GetLatentActionManager();

	if (LatentActionManager.FindExistingAction<FDelayAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == nullptr)
	{
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FDelayAction(TimeLine->GetTimelineLength(), LatentInfo));
	}

	TimeLine->Play();
}

void USlideInteractComponent::AnimateOff_Implementation(FLatentActionInfo LatentInfo)
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

void USlideInteractComponent::TurnOn_Implementation()
{
	Super::TurnOn_Implementation();
	TimelineUpdate(1.0F);

	if (TimeLine)
	{
		TimeLine->SetNewTime(TimeLine->GetTimelineLength());
	}
}

void USlideInteractComponent::TurnOff_Implementation()
{
	Super::TurnOff_Implementation();
	TimelineUpdate(0.0F);

	if (TimeLine)
	{
		TimeLine->SetNewTime(0);
	}
}

void USlideInteractComponent::TimelineUpdate(const float Value)
{
	TArray<USceneComponent*> Doors = GetTaggedComponents<USceneComponent>();

	if (!Doors.Num() || !Axis)
	{
		return;
	}

	const float Amount = FMath::Lerp(0.0F, Distance, Value);

	for (USceneComponent* Element : Doors)
	{
		FActorUtil::Slide(Element, Amount, Axis);
	}
}
