// Copyright Acinex Games 2020

#include "NonPlayerComponent.h"

#include "ReputationSystem.h"

// Sets default values for this component's properties
UNonPlayerComponent::UNonPlayerComponent()
{
}

void UNonPlayerComponent::RequestDialogue() const
{
	OnDialogueRequested.Broadcast();
}

void UNonPlayerComponent::EndConversation()
{
	SetLookAtTarget(nullptr);
}

int32 UNonPlayerComponent::GetReputation() const
{
	return ReputationSystem->GetReputation(CharacterData->Identifier);
}
