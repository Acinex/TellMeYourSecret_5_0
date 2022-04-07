// Copyright Acinex Games 2020

#include "NonPlayerCharacterController.h"

#include "NonPlayerCharacter.h"

void ANonPlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	ANonPlayerCharacter* NonPlayerCharacter = GetNonPlayerCharacter();
	if (!NonPlayerCharacter)
	{
		return;
	}

	RunBehaviorTree(NonPlayerCharacter->GetBehaviorTree());
}

ANonPlayerCharacter* ANonPlayerCharacterController::GetNonPlayerCharacter() const
{
	return Cast<ANonPlayerCharacter>(GetPawn());
}
