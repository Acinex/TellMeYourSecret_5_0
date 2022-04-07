// Copyright Acinex Games 2020

#include "SendChatMessageFlowNode.h"

#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Smartphone/Smartphone.h"

USendChatMessageFlowNode::USendChatMessageFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Smartphone");
#endif
}

void USendChatMessageFlowNode::ExecuteInput(const FName& PinName)
{
	USmartphone* Smartphone = UGameplayStatics::GetGameInstance(this)->GetSubsystem<USmartphone>();

	Smartphone->SendChatMessage(Sender, Recipient, Message, Answers);

	TriggerFirstOutput(true);
}

#if WITH_EDITOR
FString USendChatMessageFlowNode::GetNodeDescription() const
{
	return Message.ToString();
}
#endif
