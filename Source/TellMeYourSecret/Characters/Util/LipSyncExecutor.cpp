// Copyright Acinex Games 2020

#include "LipSyncExecutor.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "TellMeYourSecret/Characters/Util/LipSyncUtil.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

ULipSyncExecutor::ULipSyncExecutor(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	OnStepFinished.AddDynamic(this, &ULipSyncExecutor::FinishStep);

	MorphTargets = FLipSyncUtil::GetMorphTargets();
}

void ULipSyncExecutor::Start(UCharacterComponent* InNonPlayerComponent, const FPlayDialogueStruct Struct)
{
	NonPlayerComponent = InNonPlayerComponent;
	Data               = Struct;
	UWorld* World      = GetWorld();

	AudioComponent = NonPlayerComponent->GetOwner()->FindComponentByClass<UAudioComponent>();

	if (Data.Audio && AudioComponent)
	{
		if (Data.AudioDelay > 0)
		{
			const FTimerDelegate TimerCallback = FTimerDelegate::CreateLambda([](UAudioComponent* AudioComponent, USoundBase* AudioTrack)
			{
				AudioComponent->SetSound(AudioTrack);
				AudioComponent->Play();
			}, AudioComponent, Data.Audio);

			FTimerHandle TimerHandle;
			World->GetTimerManager().SetTimer(TimerHandle, TimerCallback, Data.AudioDelay, false);
		}
		else
		{
			AudioComponent->SetSound(Data.Audio);
			AudioComponent->Play();
		}
	}

	if (Data.Syllables.Num())
	{
		if (Data.LipSyncDelay > 0)
		{
			const FTimerDelegate TimerCallback = FTimerDelegate::CreateUObject(this, &ULipSyncExecutor::TriggerLetter);

			FTimerHandle TimerHandle;
			World->GetTimerManager().SetTimer(TimerHandle, TimerCallback, Data.LipSyncDelay, false);
		}
		else
		{
			TriggerLetter();
		}
	}

	if (Data.Montage)
	{
		const FLatentActionInfo LatentInfo;
		NonPlayerComponent->PlayAnimationMontage(Data.Montage, Data.StartSectionName, 0, LatentInfo);
	}
}

void ULipSyncExecutor::Stop() const
{
	Super::Stop();

	if (IsValid(AudioComponent))
	{
		AudioComponent->Stop();
	}

	if (Data.Montage)
	{
		NonPlayerComponent->StopAnimationMontage(Data.Montage);
	}
}

void ULipSyncExecutor::FinishStep()
{
	StepsLeft--;

	if (StepsLeft <= 0)
	{
		FinishLetter();
	}
}

void ULipSyncExecutor::FinishLetter()
{
	SyllableIndex++;

	if (SyllableIndex < Data.Syllables.Num())
	{
		TriggerLetter();
	}
	else
	{
		for (const FName MorphTarget : FLipSyncUtil::GetMorphTargets())
		{
			NonPlayerComponent->GetMesh()->SetMorphTarget(MorphTarget, 0);
		}

		OnCompleted.Broadcast();
	}
}

void ULipSyncExecutor::TriggerLetter()
{
	const FSyllable Syllable = Data.Syllables[SyllableIndex];
	CurrentDelay             = Syllable.Duration;
	StepsLeft                = MorphTargets.Num();

	FName CurrentMorphTarget;

	if (FLipSyncUtil::GetMorphTarget(Syllable.Syllable, CurrentMorphTarget))
	{
		for (const FName MorphTarget : MorphTargets)
		{
			AddMorphTargetChange(NonPlayerComponent, {MorphTarget, MorphTarget == CurrentMorphTarget ? 1.0F : 0.0F, CurrentDelay});
		}
	}
	else
	{
		AddPause();
	}
}

void ULipSyncExecutor::AddPause()
{
	StepsLeft                          = 1;
	const FTimerDelegate TimerCallback = FTimerDelegate::CreateUObject(this, &ULipSyncExecutor::FinishStep);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerCallback, CurrentDelay, false);
}
