#include "OrbitingActor.h"

#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/TimeManager.h"

AOrbitingActor::AOrbitingActor(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOrbitingActor::BeginPlay()
{
	Super::BeginPlay();
	TimeManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTimeManager>();
}

void AOrbitingActor::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Rotate(TimeManager->GetTimeOfDay().GetTotalMinutes());
}

void AOrbitingActor::Rotate(const float Time)
{
	const float Pitch = PitchCurve ? PitchCurve->GetFloatValue(Time) : 0.0F;
	const float Yaw   = YawCurve ? YawCurve->GetFloatValue(Time) : 0.0F;
	const float Roll  = RollCurve ? RollCurve->GetFloatValue(Time) : 0.0F;

	SetActorRotation({Pitch, Yaw, Roll});
}
