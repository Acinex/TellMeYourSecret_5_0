// Copyright Acinex Games 2020

#include "CharacterAnimationInstance.h"

#include "CharacterBase.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
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

	if (Character)
	{
		LeftFootEffectorLocation = Character->IKOffsetLeftFoot;
		RightFootEffectorLocation = Character->IKOffsetRightFoot;

		LeftFootSurface = Character->LeftFootSurface;
		RightFootSurface = Character->RightFootSurface;
		bIsSwimming = Character->GetMovementComponent()->IsSwimming();


		UE_LOG(LogTemp, Warning, TEXT("Character->IKOffsetLeftFoot: %f"), Character->IKOffsetLeftFoot)

		if (Character->IKOffsetLeftFoot == 0)
		{
			if (USoundBase* Sound = SelectSurfaceSound(LeftFootSurface))
			{
				UGameplayStatics::PlaySoundAtLocation(Character, Sound, LeftFootEffectorLocation);
			}
		}

		if (Character->IKOffsetRightFoot == 0)
		{
			if (USoundBase* Sound = SelectSurfaceSound(RightFootSurface))
			{
				UGameplayStatics::PlaySoundAtLocation(Character, Sound, RightFootEffectorLocation);
			}
		}
	}
}

void UCharacterAnimationInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<ACharacterBase>(TryGetPawnOwner());

	NonPlayerComponent = Character->FindComponentByClass<UNonPlayerComponent>();
}
