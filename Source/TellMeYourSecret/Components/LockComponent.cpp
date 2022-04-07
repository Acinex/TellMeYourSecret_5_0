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
}

void ULockComponent::Unlock(const FGameplayTagContainer Identity)
{
	LockedFor.RemoveTags(Identity);
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
