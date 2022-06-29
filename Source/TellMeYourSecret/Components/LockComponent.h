// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "LockComponent.generated.h"

class UInteractSubSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLockChanged, const FGameplayTagContainer&, Locks);

UCLASS(ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API ULockComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer IdentityTags;

	ULockComponent();

	UFUNCTION(BlueprintPure)
	bool IsLocked(const FGameplayTagContainer Identity) const;

	UFUNCTION(BlueprintCallable)
	void Lock(const FGameplayTagContainer Identity);

	UFUNCTION(BlueprintCallable)
	void Unlock(const FGameplayTagContainer Identity);

	UFUNCTION(BlueprintCallable)
	void SetDoorMaterial(UMaterialInstanceDynamic* InDoorMaterial);

	FGameplayTagContainer GetLocks() const;
	void SetLocks(const FGameplayTagContainer Locks);

	UPROPERTY(BlueprintAssignable)
	FLockChanged OnLockChanged;

protected:
	UPROPERTY(EditInstanceOnly, SaveGame)
	FGameplayTagContainer LockedFor;

	UPROPERTY()
	TWeakObjectPtr<UMaterialInstanceDynamic> DoorMaterial;
	void UpdateMaterial();

private:
	UPROPERTY()
	UInteractSubSystem* SubSystem;
};
