// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "FlowComponent.h"
#include "TellMeYourSecret/Characters/CharacterData.h"
#include "GameFramework/Character.h"

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
		ACharacter* Character = Cast<ACharacter>(GetOwner());
		return Cast<T>(Character->GetMesh()->GetAnimInstance());
	}

	UFUNCTION(BlueprintCallable)
	void SetAnimationOverride(UAnimationAsset* Animation, const bool bLoop) const;

	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMesh() const;

	UFUNCTION(BlueprintPure)
	float GetHunger() const;

	UFUNCTION(BlueprintCallable)
	void SetHunger(const float Value);

	UFUNCTION(BlueprintPure)
	float GetHygiene() const;

	UFUNCTION(BlueprintCallable)
	void SetHygiene(const float Value);

	UFUNCTION(BlueprintPure)
	float GetSleep() const;

	UFUNCTION(BlueprintCallable)
	void SetSleep(const float Value);

	UFUNCTION(BlueprintCallable)
	virtual bool GetLookAtLocation(FVector& LookAtLocation) const;

	UFUNCTION(BlueprintCallable)
	virtual bool GetEyeLookAtLocation(FVector& LookAtLocation) const;

	virtual void SetLookAtTarget(USkeletalMeshComponent* Target);

	UDialogueContainer* GetDialogueWidget() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCharacterData* CharacterData = nullptr;

protected:
	/** Percentage value of the hygiene */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintSetter=SetHygiene)
	float Hygiene = 1.0F;

	/** Percentage value of the hunger */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintSetter=SetHunger)
	float Hunger = 1.0F;

	/** Percentage value of the hunger */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintSetter=SetSleep)
	float Sleep = 1.0F;

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UDialogueContainer> DialogueWidgetClass;
	
	UPROPERTY()
	UReputationSystem* ReputationSystem = nullptr;

	UPROPERTY()
	TSoftObjectPtr<USkeletalMeshComponent> LookAtActorPtr;

	bool  bSwitchEyes;
	float LastEyeSwitch;
	float NextEyeSwitch;
	FName CurrentEye = TEXT("lEye");

private:
	UPROPERTY()
	UDialogueContainer* DialogueWidget = nullptr;
};
