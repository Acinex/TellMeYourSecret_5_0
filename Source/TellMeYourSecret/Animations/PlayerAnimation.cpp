// Copyright Acinex Games 2020

#include "PlayerAnimation.h"

#include "AnimGraphRuntime/Public/KismetAnimationLibrary.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TellMeYourSecret/Characters/PlayerCharacter.h"

void UPlayerAnimation::NativeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* PawnOwner = TryGetPawnOwner();

	if (!PawnOwner)
	{
		return;
	}

	const FVector Velocity = PawnOwner->GetVelocity();

	FRotator ActorRotation = PawnOwner->GetActorRotation();
	ActorRotation.Normalize();
	Speed        = Velocity.Size();
	Direction    = UKismetAnimationLibrary::CalculateDirection(Velocity, ActorRotation);
	bIsCrouching = PawnOwner->GetMovementComponent()->IsCrouching();

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(PawnOwner);
	if (!PlayerCharacter)
	{
		return;
	}

	FRotator ControlRotation = PawnOwner->GetControlRotation();
	ControlRotation.Normalize();

	if (ControlRotation.Yaw < -90 && ActorRotation.Yaw > 90)
	{
		ControlRotation.Yaw += 360;
	}
	if (ActorRotation.Yaw < -90 && ControlRotation.Yaw > 90)
	{
		ActorRotation.Yaw += 360;
	}

	HeadRotation         = {0, FMath::Clamp(ControlRotation.Yaw - ActorRotation.Yaw, -60.0F, 60.0F), ControlRotation.Pitch * -1};
	bIsShowingSmartphone = PlayerCharacter->IsShowingSmartphone();
	bIsFirstPerson       = PlayerCharacter->IsFirstPerson();
}

void UPlayerAnimation::LeftFootStep()
{
	APawn* PawnOwner = TryGetPawnOwner();

	if (!PawnOwner)
	{
		return;
	}

	const FVector Start = PawnOwner->GetActorLocation();
	const FVector End   = Start - FVector(0, 0, 150);

	FHitResult Hit;
	if (UKismetSystemLibrary::LineTraceSingle(PawnOwner, Start, End, TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::None, Hit, true))
	{
		if (USoundBase* Sound = SelectSurfaceSound(UGameplayStatics::GetSurfaceType(Hit)))
		{
			UGameplayStatics::PlaySoundAtLocation(PawnOwner, Sound, Hit.Location);
		}
	}
}

void UPlayerAnimation::RightFootStep()
{
	APawn* PawnOwner = TryGetPawnOwner();

	if (!PawnOwner)
	{
		return;
	}

	const FVector Start = PawnOwner->GetActorLocation();
	const FVector End   = Start - FVector(0, 0, 150);

	FHitResult Hit;
	if (UKismetSystemLibrary::LineTraceSingle(PawnOwner, Start, End, TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::None, Hit, true))
	{
		if (USoundBase* Sound = SelectSurfaceSound(UGameplayStatics::GetSurfaceType(Hit)))
		{
			UGameplayStatics::PlaySoundAtLocation(PawnOwner, Sound, Hit.Location);
		}
	}
}
