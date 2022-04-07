// Copyright Acinex Games 2020

#include "HeightAdjustComponent.h"

#include "TellMeYourSecret/Utils/CompletablePendingLatentAction.h"
#include "TellMeYourSecret/Log.h"

const FName UHeightAdjustComponent::Wanted_Tag = FName("Height");

void UHeightAdjustComponent::AnimateOn_Implementation(const FLatentActionInfo LatentInfo)
{
	FCompletablePendingLatentAction* Action = new FCompletablePendingLatentAction(LatentInfo);

	GetWorld()->GetLatentActionManager().AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	UpdateHeight();
	Action->Complete();
}

void UHeightAdjustComponent::AnimateOff_Implementation(const FLatentActionInfo LatentInfo)
{
	FCompletablePendingLatentAction* Action = new FCompletablePendingLatentAction(LatentInfo);

	GetWorld()->GetLatentActionManager().AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	UpdateHeight();
	Action->Complete();
}

void UHeightAdjustComponent::TurnOn_Implementation()
{
	UpdateHeight();
}

void UHeightAdjustComponent::TurnOff_Implementation()
{
	UpdateHeight();
}

void UHeightAdjustComponent::UpdateHeight() const
{
	const TArray<USceneComponent*> SceneComponents = GetTaggedComponents<USceneComponent>();
	if (Heights.Num() < SceneComponents.Num())
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("Number of Heights should be %d for %s"), SceneComponents.Num(), *GetOwner()->GetName())
		return;
	}

	for (int32 i = 0; i < SceneComponents.Num(); i++)
	{
		FVector NewLocation = SceneComponents[i]->GetRelativeLocation();
		NewLocation.Z       = Heights[i];
		SceneComponents[i]->SetRelativeLocation(NewLocation);
	}
}
