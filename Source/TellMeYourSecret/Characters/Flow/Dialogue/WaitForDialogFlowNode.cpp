// Copyright Acinex Games 2020

#include "WaitForDialogFlowNode.h"

#include "TellMeYourSecret/Characters/NonPlayerComponent.h"

UWaitForDialogFlowNode::UWaitForDialogFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Dialogue");
#endif
}

void UWaitForDialogFlowNode::ObserveActor(TWeakObjectPtr<AActor> Actor, TWeakObjectPtr<UFlowComponent> Component)
{
	if (!RegisteredActors.Contains(Actor))
	{
		if (UNonPlayerComponent* NonPlayerComponent = Cast<UNonPlayerComponent>(Component))
		{
			RegisteredActors.Emplace(Actor, NonPlayerComponent);

			TWeakObjectPtr<UWaitForDialogFlowNode> SelfWeakPtr(this);
			NonPlayerComponent->OnDialogueRequested.AddWeakLambda(this, [SelfWeakPtr]()
			{
				if (SelfWeakPtr.IsValid())
				{
					SelfWeakPtr->OnEventReceived();
				}
			});
		}
	}
}

void UWaitForDialogFlowNode::ForgetActor(TWeakObjectPtr<AActor> Actor, TWeakObjectPtr<UFlowComponent> Component)
{
	UNonPlayerComponent* NonPlayerComponent = Cast<UNonPlayerComponent>(Component);
	ensureAlways(NonPlayerComponent);

	NonPlayerComponent->OnDialogueRequested.RemoveAll(this);
}
