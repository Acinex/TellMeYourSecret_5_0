// Copyright Acinex Games 2020

#include "CharacterAnimationInstance.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimationInstance::SetAnimOverride(UAnimationAsset* Animation, const bool bLoop)
{
	AnimationOverride = Animation;
	bLoopOverride = bLoop;
	bUseOverride = IsValid(AnimationOverride);
}

void UCharacterAnimationInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (NonPlayerComponent)
	{
		Speed = UKismetMathLibrary::VSize(NonPlayerComponent->GetOwner()->GetVelocity());
		bUseLookAt = NonPlayerComponent->GetLookAtLocation(LookAtLocation);
		bUseEyeLookAt = NonPlayerComponent->GetEyeLookAtLocation(EyeLookAtLocation);
	}

	APawn* PawnOwner = TryGetPawnOwner();
	if (PawnOwner != nullptr)
	{
		bIsSwimming = PawnOwner->GetMovementComponent()->IsSwimming();
	}
	CalculateBlink(DeltaSeconds);

	LastBlink += DeltaSeconds;
	if (LastBlink >= NextBlink)
	{
		bBLinking = true;
		LastBlink = 0;
	}
}

void UCharacterAnimationInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* PawnOwner = TryGetPawnOwner();

	NonPlayerComponent = PawnOwner->FindComponentByClass<UNonPlayerComponent>();
}

void UCharacterAnimationInstance::CalculateBlink(const float DeltaSeconds)
{
	const float UpperEnd = 40.0F;
	const float LowerEnd = -5.0F;

	if (bKeepEyesClosed)
	{
		UpperEyeLidRotation.Roll = UpperEnd;
		LowerEyeLidRotation.Roll = LowerEnd;
		return;
	}

	if (!bBLinking)
	{
		UpperEyeLidRotation.Roll = 0;
		LowerEyeLidRotation.Roll = 0;
		return;
	}

	if (bBlinkPhaseDown)
	{
		UpperEyeLidRotation.Roll = UKismetMathLibrary::FInterpTo_Constant(
			UpperEyeLidRotation.Roll, UpperEnd, DeltaSeconds, 2500);
		LowerEyeLidRotation.Roll = UKismetMathLibrary::FInterpTo_Constant(
			LowerEyeLidRotation.Roll, LowerEnd, DeltaSeconds, 2500);

		if (UKismetMathLibrary::NearlyEqual_FloatFloat(UpperEyeLidRotation.Roll, UpperEnd, 0.000001))
		{
			bBlinkPhaseDown = false;
		}
		return;
	}

	UpperEyeLidRotation.Roll = UKismetMathLibrary::FInterpTo_Constant(UpperEyeLidRotation.Roll, 0, DeltaSeconds, 2500);
	LowerEyeLidRotation.Roll = UKismetMathLibrary::FInterpTo_Constant(LowerEyeLidRotation.Roll, 0, DeltaSeconds, 2500);

	if (UKismetMathLibrary::NearlyEqual_FloatFloat(UpperEyeLidRotation.Roll, 0, 0.000001))
	{
		bBLinking = false;
		bBlinkPhaseDown = true;
		NextBlink = UKismetMathLibrary::RandomFloatInRange(4.5, 5.5);
	}
}
