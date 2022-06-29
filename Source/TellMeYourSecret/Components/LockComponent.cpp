// Copyright Acinex Games 2020

#include "LockComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/InteractSubSystem.h"


// Sets default values for this component's properties
ULockComponent::ULockComponent()
{
}

bool ULockComponent::IsLocked(const FGameplayTagContainer Identity) const
{
	return LockedFor.HasAll(Identity);
}

void ULockComponent::Lock(const FGameplayTagContainer Identity)
{
	LockedFor.AppendTags(Identity);
	UpdateMaterial();
	OnLockChanged.Broadcast(LockedFor);
}

void ULockComponent::Unlock(const FGameplayTagContainer Identity)
{
	LockedFor.RemoveTags(Identity);
	UpdateMaterial();
	OnLockChanged.Broadcast(LockedFor);
}

void ULockComponent::SetDoorMaterial(UMaterialInstanceDynamic* InDoorMaterial)
{
	DoorMaterial = InDoorMaterial;
	if (IsValid(InDoorMaterial))
	{
		UpdateMaterial();
	}
}

FGameplayTagContainer ULockComponent::GetLocks() const
{
	FGameplayTagContainer LockStatesCopy = LockedFor;
	return LockStatesCopy;
}

void ULockComponent::SetLocks(const FGameplayTagContainer Locks)
{
	LockedFor = Locks;
}

void ULockComponent::UpdateMaterial()
{
	if (!DoorMaterial.IsValid())
	{
		return;
	}

	static const FGameplayTag Player = FGameplayTag::RequestGameplayTag("Character.Player");

	static const FGameplayTagContainer Container(Player);
	const FLinearColor Color = IsLocked(Container) ? FLinearColor::Red : FLinearColor::Blue;

	DoorMaterial->SetVectorParameterValue("EmissiveColor", Color);
}
