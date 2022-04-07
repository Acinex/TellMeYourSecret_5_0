// Copyright Acinex Games 2020

#include "ApproachComponent.h"

// Sets default values for this component's properties
UApproachComponent::UApproachComponent()
{
}

bool UApproachComponent::IsFor(const FGameplayTagContainer Other) const
{
	if (IsForAll())
	{
		return true;
	}

	return Tags.HasAll(Other);
}

bool UApproachComponent::IsForAll() const
{
	return Tags.IsEmpty();
}

bool UApproachComponent::IsOccupied() const
{
	return bOccupied;
}

void UApproachComponent::SetOccupied(const bool InbOccupied)
{
	bOccupied = InbOccupied;
}