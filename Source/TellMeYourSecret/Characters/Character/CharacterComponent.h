// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "FlowComponent.h"
#include "TellMeYourSecret/Characters/CharacterData.h"
#include "GameFramework/Character.h"
#include "TellMeYourSecret/Characters/Util/MorphTargetChange.h"

#include "CharacterComponent.generated.h"

class UReputationSystem;
class UDialogueContainer;
class UCharacterAnimationInstance;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API UCharacterComponent : public UFlowComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterComponent();

	UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo"))
	void PlayAnimationMontage(UAnimMontage* Montage, FName StartSectionName, const float TimeToStartMontageAt, struct FLatentActionInfo LatentInfo) const;
	UFUNCTION(BlueprintCallable)
	void StopAnimationMontage(UAnimMontage* Montage) const;
	UFUNCTION(BlueprintCallable)
	void PauseAnimationMontage() const;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	template <class T>
	T* GetAnimInstance() const
	{
		const ACharacter* Character = Cast<ACharacter>(GetOwner());
		return Cast<T>(Character->GetMesh()->GetAnimInstance());
	}

	UFUNCTION(BlueprintCallable)
	void SetAnimationOverride(UAnimSequenceBase* Animation, const bool bLoop) const;
	
	void SetEyesClosed(const bool bEyesClosed)
	{
		bKeepEyesClosed = bEyesClosed;
		LastBlink       = 0;
	}

	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMesh() const;

	UFUNCTION(BlueprintCallable)
	virtual bool GetLookAtLocation(FVector& LookAtLocation) const;

	UFUNCTION(BlueprintCallable)
	virtual bool GetEyeLookAtLocation(FVector& LookAtLocation) const;

	virtual void SetLookAtTarget(USkeletalMeshComponent* Target);

	UDialogueContainer* GetDialogueWidget() const;
	void SetMorphTarget(const FName& Name, float Value) const;
	void ClearMorphTargets() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCharacterData* CharacterData = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UDialogueContainer> DialogueWidgetClass;

	UPROPERTY()
	UReputationSystem* ReputationSystem = nullptr;

	UPROPERTY()
	bool bKeepEyesClosed;

	UPROPERTY()
	TSoftObjectPtr<USkeletalMeshComponent> LookAtActorPtr;

	bool bSwitchEyes;
	float LastEyeSwitch;
	float NextEyeSwitch;
	FName CurrentEye = TEXT("lEye");
	
	UPROPERTY(BlueprintReadOnly, Category=Blink)
	float EyeCloseMorph;

private:
	UPROPERTY()
	UDialogueContainer* DialogueWidget = nullptr;

	bool bBLinking;
	bool bBlinkPhaseDown;
	float LastBlink;
	float NextBlink;

	void CalculateBlink(const float DeltaSeconds);
};
