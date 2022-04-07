// Copyright Acinex Games 2020

#include "CharacterComponent.h"

#include "CharacterAnimationInstance.h"
#include "Blueprint/UserWidget.h"
#include "TellMeYourSecret/Characters/PlayAnimationAction.h"
#include "TellMeYourSecret/Characters/UI/DialogueContainer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TellMeYourSecret/Characters/ReputationSystem.h"

// Sets default values for this component's properties
UCharacterComponent::UCharacterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterComponent::PlayAnimationMontage(UAnimMontage* Montage, const FName StartSectionName, const float TimeToStartMontageAt, const FLatentActionInfo LatentInfo) const
{
	ACharacter*           Character           = Cast<ACharacter>(GetOwner());
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
	ACharacter*    Character    = Cast<ACharacter>(GetOwner());
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}

	FAnimMontageInstance* ActiveMontageInstance = AnimInstance->GetActiveMontageInstance();
	if (ActiveMontageInstance)
	{
		ActiveMontageInstance->Pause();
	}
}

void UCharacterComponent::TickComponent(const float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
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

void UCharacterComponent::SetAnimationOverride(UAnimationAsset* Animation, const bool bLoop) const
{
	GetAnimInstance<UCharacterAnimationInstance>()->SetAnimOverride(Animation, bLoop);
}

USkeletalMeshComponent* UCharacterComponent::GetMesh() const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	return Character->GetMesh();
}

float UCharacterComponent::GetHunger() const
{
	return Hunger;
}

void UCharacterComponent::SetHunger(const float Value)
{
	Hunger = FMath::Clamp(Value, 0.0F, 1.0F);
}

float UCharacterComponent::GetHygiene() const
{
	return Hygiene;
}

void UCharacterComponent::SetHygiene(const float Value)
{
	Hygiene = FMath::Clamp(Value, 0.0F, 1.0F);
}

float UCharacterComponent::GetSleep() const
{
	return Sleep;
}

void UCharacterComponent::SetSleep(const float Value)
{
	Sleep = FMath::Clamp(Value, 0.0F, 1.0F);
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
