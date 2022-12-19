// Copyright Acinex Games 2020

#include "CharacterComponent.h"

#include "CharacterAnimationInstance.h"
#include "Blueprint/UserWidget.h"
#include "TellMeYourSecret/Characters/PlayAnimationAction.h"
#include "TellMeYourSecret/Characters/UI/DialogueContainer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/TellMeYourSecretGameSettings.h"
#include "TellMeYourSecret/Characters/ReputationSystem.h"
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"

// Sets default values for this component's properties
UCharacterComponent::UCharacterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UCharacterComponent::PlayAnimationMontage(UAnimMontage* Montage, const FName StartSectionName, const float TimeToStartMontageAt, const FLatentActionInfo LatentInfo) const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	FLatentActionManager& LatentActionManager = GetWorld()->GetLatentActionManager();

	if (LatentActionManager.FindExistingAction<FPlayAnimationAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == nullptr)
	{
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FPlayAnimationAction(Character, Montage, StartSectionName, TimeToStartMontageAt, LatentInfo));
	}
}

void UCharacterComponent::StopAnimationMontage(UAnimMontage* Montage) const
{
	Cast<ACharacter>(GetOwner())->StopAnimMontage(Montage);
}

void UCharacterComponent::PauseAnimationMontage() const
{
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	const UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}

	if (FAnimMontageInstance* ActiveMontageInstance = AnimInstance->GetActiveMontageInstance())
	{
		ActiveMontageInstance->Pause();
	}
}

void UCharacterComponent::TickComponent(const float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CalculateBlink(DeltaTime);

	LastBlink += DeltaTime;
	if (LastBlink >= NextBlink)
	{
		bBLinking = true;
		LastBlink = 0;
	}

	static UTellMeYourSecretGameSettings* Settings = UTellMeYourSecretGameSettings::Get();

	SetMorphTarget(Settings->EyesClosedName, EyeCloseMorph);

	if (!bSwitchEyes || !LookAtActorPtr.IsValid())
	{
		return;
	}

	LastEyeSwitch += DeltaTime;

	if (LastEyeSwitch >= NextEyeSwitch)
	{
		if (CurrentEye == TEXT("rEye"))
		{
			CurrentEye = TEXT("lEye");
		}
		else
		{
			CurrentEye = TEXT("rEye");
		}

		NextEyeSwitch = UKismetMathLibrary::RandomFloatInRange(0.2, 0.8);
		LastEyeSwitch = 0;
	}
}

void UCharacterComponent::SetAnimationOverride(UAnimSequenceBase* Animation, const bool bLoop) const
{
	GetAnimInstance<UCharacterAnimationInstance>()->SetAnimOverride(Animation, bLoop);
}

USkeletalMeshComponent* UCharacterComponent::GetMesh() const
{
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	return Character->GetMesh();
}

bool UCharacterComponent::GetLookAtLocation(FVector& LookAtLocation) const
{
	if (!LookAtActorPtr.IsValid())
	{
		return false;
	}

	const FVector HeadLocation = LookAtActorPtr->GetBoneLocation(TEXT("CenterBrow"));

	if (FVector::Distance(GetOwner()->GetActorLocation(), HeadLocation) > 500)
	{
		return false;
	}

	LookAtLocation = HeadLocation;

	return true;
}

bool UCharacterComponent::GetEyeLookAtLocation(FVector& LookAtLocation) const
{
	if (!LookAtActorPtr.IsValid())
	{
		return false;
	}

	if (bSwitchEyes)
	{
		LookAtLocation = LookAtActorPtr->GetBoneLocation(CurrentEye);
	}
	else
	{
		LookAtLocation = LookAtActorPtr->GetBoneLocation(TEXT("CenterBrow"));
	}
	return true;
}

void UCharacterComponent::SetLookAtTarget(USkeletalMeshComponent* Target)
{
	LookAtActorPtr = Target;

	bSwitchEyes = false;
	if (LookAtActorPtr.IsValid() && CharacterData->Identifier != ECharacterIdentifier::Player)
	{
		if (ReputationSystem->GetReputation(CharacterData->Identifier) > 10)
		{
			bSwitchEyes = true;
		}
	}
}

UDialogueContainer* UCharacterComponent::GetDialogueWidget() const
{
	if (IsValid(DialogueWidgetClass))
	{
		return CreateWidget<UDialogueContainer>(GetWorld()->GetFirstPlayerController(), DialogueWidgetClass);
	}

	return nullptr;
}

void UCharacterComponent::SetMorphTarget(const FName& Name, const float Value) const
{
	const float* Current = GetMesh()->GetMorphTargetCurves().Find(FName("Genesis8Female__" + Name.ToString()));
	if (Current && *Current == Value)
	{
		return;
	}

	TArray<USkeletalMeshComponent*> Components;
	GetOwner()->GetComponents<USkeletalMeshComponent>(Components);

	for (USkeletalMeshComponent* Component : Components)
	{
		if (!IsValid(Component->SkeletalMesh))
		{
			continue;
		}

		/*
		 * Because we have different names for the morphtargets we can't just use the complete name.
		 * But all names have the same pattern and end with the specific morphtarget name.
		 *
		 * e.g. Gen8__smile
		 *      Gen8Eye__smile
		 */
		for (const UMorphTarget* MorphTarget : Component->SkeletalMesh->GetMorphTargets())
		{
			if (MorphTarget->GetName().EndsWith(Name.ToString()))
			{
				Component->SetMorphTarget(MorphTarget->GetFName(), Value);
				break;
			}
		}
	}
}

void UCharacterComponent::ClearMorphTargets() const
{
	TArray<USkeletalMeshComponent*> Components;
	GetOwner()->GetComponents<USkeletalMeshComponent>(Components);

	for (USkeletalMeshComponent* Component : Components)
	{
		Component->ClearMorphTargets();
	}
}

// Called when the game starts
void UCharacterComponent::BeginPlay()
{
	Super::BeginPlay();
	ReputationSystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UReputationSystem>();

	/*
	 * Since the character's name can be changed by the settings we need to
	 * override this characterData with those from the reputationSystem so we can see the name in the dialogues
	 */
	if (CharacterData)
	{
		CharacterData = ReputationSystem->GetCharacter(CharacterData->Identifier);
	}
}

void UCharacterComponent::CalculateBlink(const float DeltaSeconds)
{
	static constexpr float UpperEnd = 1.0F;

	if (bKeepEyesClosed)
	{
		EyeCloseMorph = UpperEnd;
		return;
	}

	if (!bBLinking)
	{
		EyeCloseMorph = 0;
		return;
	}

	if (bBlinkPhaseDown)
	{
		EyeCloseMorph = UKismetMathLibrary::FInterpTo_Constant(EyeCloseMorph, UpperEnd, DeltaSeconds, 2500);

		if (UKismetMathLibrary::NearlyEqual_FloatFloat(EyeCloseMorph, UpperEnd, 0.000001))
		{
			bBlinkPhaseDown = false;
		}
		return;
	}

	EyeCloseMorph = UKismetMathLibrary::FInterpTo_Constant(EyeCloseMorph, 0, DeltaSeconds, 2500);

	if (UKismetMathLibrary::NearlyEqual_FloatFloat(EyeCloseMorph, 0, 0.000001))
	{
		bBLinking = false;
		bBlinkPhaseDown = true;
		NextBlink = UKismetMathLibrary::RandomFloatInRange(4.5, 5.5);
	}
}
