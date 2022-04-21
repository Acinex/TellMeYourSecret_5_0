// Copyright Acinex Games 2020

#include "OrbitingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/TimeManager.h"


UOrbitingComponent::UOrbitingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOrbitingComponent::Rotate(const float Time) const
{
	const float Pitch = PitchCurve ? PitchCurve->GetFloatValue(Time) : 0.0F;
	const float Yaw = YawCurve ? YawCurve->GetFloatValue(Time) : 0.0F;
	const float Roll = RollCurve ? RollCurve->GetFloatValue(Time) : 0.0F;

	GetOwner()->SetActorRotation({Pitch, Yaw, Roll});
}

void UOrbitingComponent::BeginPlay()
{
	Super::BeginPlay();

	TimeManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTimeManager>();

	SetComponentTickEnabled(PitchCurve || YawCurve || RollCurve);
}

void UOrbitingComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Rotate(TimeManager->GetTimeOfDay().GetTotalMinutes());
}
