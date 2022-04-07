// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/CharacterIdentifier.h"
#include "Nodes/FlowNode.h"
#include "SendChatMessageFlowNode.generated.h"

/**
 * Sends a chat message from sender to recipient
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Send chat message"))
class TELLMEYOURSECRET_API USendChatMessageFlowNode : public UFlowNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText Message;

	UPROPERTY(EditAnywhere)
	ECharacterIdentifier Recipient;

	UPROPERTY(EditAnywhere)
	ECharacterIdentifier Sender;

	UPROPERTY(EditAnywhere)
	TArray<FText> Answers;

	USendChatMessageFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif
};
