#include "PlayAnimationAction.h"

#include "GameFramework/Character.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "TellMeYourSecret/Log.h"

FPlayAnimationAction::FPlayAnimationAction(ACharacter* Character, UAnimationAsset* Animation, const FLatentActionInfo& LatentInfo):
	ExecutionFunction(LatentInfo.ExecutionFunction)
  , OutputLink(LatentInfo.Linkage)
  , CallbackTarget(LatentInfo.CallbackTarget)
{
	Character->GetMesh()->PlayAnimation(Animation, false);

	TimeRemaining = Character->GetMesh()->GetSingleNodeInstance()->GetLength();
}

FPlayAnimationAction::FPlayAnimationAction(ACharacter* Character, UAnimMontage* Animation, const FName StartSectionName, const float TimeToStartMontageAt, const FLatentActionInfo& LatentInfo):
	ExecutionFunction(LatentInfo.ExecutionFunction)
  , OutputLink(LatentInfo.Linkage)
  , CallbackTarget(LatentInfo.CallbackTarget)
{
	TimeRemaining    = PlayMontage(Character, Animation, StartSectionName, TimeToStartMontageAt);
	AnimationMontage = Animation;
}

void FPlayAnimationAction::UpdateOperation(FLatentResponse& Response)
{
	if (AnimationMontage)
	{
		Response.FinishAndTriggerIf(bMontageEnded, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}

	TimeRemaining -= Response.ElapsedTime();
	Response.FinishAndTriggerIf(TimeRemaining <= 0.0f, ExecutionFunction, OutputLink, CallbackTarget);
}

float FPlayAnimationAction::PlayMontage(ACharacter* Character, UAnimMontage* AnimMontage, const FName StartSectionName, const float TimeToStartMontageAt)
{
	UAnimInstance* AnimInstance = (Character->GetMesh()) ? Character->GetMesh()->GetAnimInstance() : nullptr;
	if (AnimMontage && AnimInstance)
	{
		FAnimMontageInstance** Instance = AnimInstance->MontageInstances.FindByPredicate([AnimMontage](const FAnimMontageInstance* It)
		{
			return AnimMontage == It->Montage && !It->IsStopped();
		});

		float Duration;

		if (Instance)
		{
			(*Instance)->Play();
			Duration = AnimMontage->GetPlayLength() - (*Instance)->GetPosition();
		}
		else
		{
			Duration = AnimInstance->Montage_Play(AnimMontage, 1, EMontagePlayReturnType::MontageLength, TimeToStartMontageAt);
			// Start at a given Section.
			if (StartSectionName != NAME_None)
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, AnimMontage);
			}
		}

		MontageEndedDelegate.BindLambda([this,AnimMontage](UAnimMontage* Montage, bool bInterrupted)
		{
			UE_LOG(LogTellMeYourSecret, Log, TEXT("Montage %s ended"), *Montage->GetName())
			if (Montage == AnimMontage)
			{
				bMontageEnded = true;
			}
		});
		AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, AnimMontage);
		UE_LOG(LogTellMeYourSecret, Log, TEXT("Montage duration: %f"), Duration)
		return Duration;
	}

	return 0.f;
}
