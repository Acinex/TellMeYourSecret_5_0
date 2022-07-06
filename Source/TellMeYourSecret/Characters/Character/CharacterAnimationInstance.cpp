// Copyright Acinex Games 2020

#include "CharacterAnimationInstance.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimationInstance::SetAnimOverride(UAnimSequenceBase* Animation, const bool bLoop)
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

	const APawn* PawnOwner = TryGetPawnOwner();
	if (PawnOwner != nullptr)
	{
		bIsSwimming = PawnOwner->GetMovementComponent()->IsSwimming();
	}
}

void UCharacterAnimationInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	const APawn* PawnOwner = TryGetPawnOwner();

	NonPlayerComponent = PawnOwner->FindComponentByClass<UNonPlayerComponent>();
}
