// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Character/CharacterComponent.h"
#include "NonPlayerComponent.generated.h"

class UDataTable;
class UGOAPAction;
class UDialogueContainer;
class UCharacterData;
class UReputationSystem;

DECLARE_MULTICAST_DELEGATE(FStartDialogue);

UCLASS(ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API UNonPlayerComponent : public UCharacterComponent
{
	GENERATED_BODY()

public:
	FStartDialogue OnDialogueRequested;

	UNonPlayerComponent();

	void RequestDialogue() const;
	void EndConversation();

	int32 GetReputation() const;
};
