// Copyright Acinex Games 2020

#include "AnimateInteractComponent.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "LatentActions.h"

class FAnimateLatentAction : public FPendingLatentAction
{
public:
	FAnimateLatentAction(TArray<USkeletalMeshComponent*> InComponents, const FLatentActionInfo LatentInfo, bool bReverse);

	virtual void UpdateOperation(FLatentResponse& Response) override;

private:
	FName                           ExecutionFunction;
	int32                           LinkID = 0;
	FWeakObjectPtr                  CallbackTarget;
	TArray<USkeletalMeshComponent*> Components;
	float                           Time;
};

FAnimateLatentAction::FAnimateLatentAction(TArray<USkeletalMeshComponent*> InComponents, const FLatentActionInfo LatentInfo, const bool bReverse):
	ExecutionFunction(LatentInfo.ExecutionFunction)
  , LinkID(LatentInfo.Linkage)
  , CallbackTarget(LatentInfo.CallbackTarget)
{
	Time = 0;
	for (USkeletalMeshComponent* Component : Components)
	{
		Component->SetPlayRate(bReverse ? -1.0F : 1.0F);
		Component->Play(false);

		if (Component->GetSingleNodeInstance())
		{
			Time = FMath::Max(Component->GetSingleNodeInstance()->GetLength(), Time);
		}
	}
}

void FAnimateLatentAction::UpdateOperation(FLatentResponse& Response)
{
	Time -= Response.ElapsedTime();

	Response.FinishAndTriggerIf(Time == 0.0F, ExecutionFunction, LinkID, CallbackTarget);
}

const FName UAnimateInteractComponent::Wanted_Tag = FName("Animate");

void UAnimateInteractComponent::AnimateOn_Implementation(FLatentActionInfo LatentInfo)
{
	FLatentActionManager& LatentActionManager = GetWorld()->GetLatentActionManager();

	if (LatentActionManager.FindExistingAction<FAnimateLatentAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == nullptr)
	{
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FAnimateLatentAction(GetTaggedComponents<USkeletalMeshComponent>(), LatentInfo, false));
	}
}

void UAnimateInteractComponent::AnimateOff_Implementation(FLatentActionInfo LatentInfo)
{
	FLatentActionManager& LatentActionManager = GetWorld()->GetLatentActionManager();

	if (LatentActionManager.FindExistingAction<FAnimateLatentAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == nullptr)
	{
		LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FAnimateLatentAction(GetTaggedComponents<USkeletalMeshComponent>(), LatentInfo, true));
	}
}

void UAnimateInteractComponent::TurnOn_Implementation()
{
	for (USkeletalMeshComponent* Door : GetTaggedComponents<USkeletalMeshComponent>())
	{
		Door->InitAnim(true);
		if (Door->GetSingleNodeInstance())
		{
			Door->SetPosition(Door->GetSingleNodeInstance()->GetLength());
		}
	}
}

void UAnimateInteractComponent::TurnOff_Implementation()
{
	for (USkeletalMeshComponent* Door : GetTaggedComponents<USkeletalMeshComponent>())
	{
		Door->InitAnim(true);
		Door->SetPosition(0);
	}
}
