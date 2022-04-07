// Copyright Acinex Games 2020

#include "LockUnlockObjectFlowNode.h"

#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Actors/Interact/StatefulInteractiveObject.h"
#include "TellMeYourSecret/Components/LockComponent.h"
#include "TellMeYourSecret/GameInstances/InteractSubSystem.h"

ULockUnlockObjectFlowNode::ULockUnlockObjectFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Action");
#endif
}

void ULockUnlockObjectFlowNode::ExecuteInput(const FName& PinName)
{
	const AInteractiveObject* InteractiveObject = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UInteractSubSystem>()->FindObject(InteractionIdentityTags, EGameplayContainerMatchType::All);
	if (!IsValid(InteractiveObject))
	{
		return AddStatusReport(TEXT("No Interactive Object found"));
	}

	ULockComponent* LockComponent = InteractiveObject->FindComponentByClass<ULockComponent>();
	if (!IsValid(LockComponent))
	{
		return AddStatusReport(TEXT("The Object can't be locked"));
	}

	if (bLock)
	{
		LockComponent->Lock(IdentityTags);
	}
	else
	{
		LockComponent->Unlock(IdentityTags);
	}

	TriggerFirstOutput(true);
}
