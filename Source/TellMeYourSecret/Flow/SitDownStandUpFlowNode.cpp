// Copyright Acinex Games 2020

#include "SitDownStandUpFlowNode.h"

#include "AIController.h"
#include "ApproachAction.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "Components/CapsuleComponent.h"
#include "TellMeYourSecret/Components/ApproachComponent.h"
#include "TellMeYourSecret/Log.h"

USitDownStandUpFlowNode::USitDownStandUpFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Action");
#endif

	InputPins.Empty();
	InputPins.Add({TEXT("Sit"), TEXT("To sit down")});
	InputPins.Add({TEXT("Stand"), TEXT("To stand up")});

	OutputPins.Add({TEXT("Idle"), TEXT("After idle was started")});
	OutputPins.Add({TEXT("Complete"), TEXT("After stand up")});
	OutputPins.Add({TEXT("Failed"), TEXT("Could not approach. Might be occupied or not available for this character")});
}

void USitDownStandUpFlowNode::ExecuteInput(const FName& PinName)
{
	if (PinName.IsEqual(TEXT("Sit")))
	{
		if (Approach())
		{
			TriggerOutput(TEXT("Out"));
		}
		else
		{
			TriggerOutput(TEXT("Failed"));
		}
	}
	else if (PinName.IsEqual(TEXT("Stand")))
	{
		DoStandUp();
	}
}

void USitDownStandUpFlowNode::FixNode(UEdGraphNode* NewGraph)
{
	Super::FixNode(NewGraph);
	OutputPins.Remove({TEXT("Failed"), TEXT("Could not approach. Might be occupied or not available for this character")});
	OutputPins.Add({TEXT("Failed"), TEXT("Could not approach. Might be occupied or not available for this character")});
}

#if WITH_EDITOR
FString USitDownStandUpFlowNode::GetStatusString() const
{
	FString Result = Super::GetStatusString();
	if (!Result.IsEmpty())
	{
		Result.Append(LINE_TERMINATOR);
	}

	switch (State)
	{
	case ESitDownStandUpFlowExecutionState::Moving:
		Result.Append(TEXT("Moving to Chair"));
		break;
	case ESitDownStandUpFlowExecutionState::SitDown:
		Result.Append(TEXT("Sitting down"));
		break;
	case ESitDownStandUpFlowExecutionState::Idle:
		Result.Append(TEXT("Idle"));
		break;
	case ESitDownStandUpFlowExecutionState::StandUp:
		Result.Append(TEXT("Standing up"));
		break;
	default: return Result;
	}

	return Result;
}
#endif

void USitDownStandUpFlowNode::OnLoad_Implementation()
{
	if (ApproachComponent.IsValid())
	{
		TArray<UApproachComponent*> Approaches;
		FindActor(ChairTags)->GetComponents<UApproachComponent>(Approaches);
		ApproachComponent = *Approaches.FindByPredicate([this](const UApproachComponent* Component)
		{
			return Component == ApproachComponent.Get();
		});
	}

	switch (State)
	{
	case ESitDownStandUpFlowExecutionState::Moving:
		Approach();
		break;
	case ESitDownStandUpFlowExecutionState::SitDown:
	case ESitDownStandUpFlowExecutionState::Idle:
		ApplyIdle();
		break;
	default: ;
	}
}

bool USitDownStandUpFlowNode::Approach()
{
	State = ESitDownStandUpFlowExecutionState::Moving;

	UApproachAction* ApproachAction = NewObject<UApproachAction>(this);
	ApproachAction->OnComplete.AddUObject(this, &USitDownStandUpFlowNode::Approached);

	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();
	const bool bApproach = ApproachAction->Approach(FindActor(ChairTags), Cast<AAIController>(Cast<APawn>(NonPlayerComponent->GetOwner())->GetController()), NonPlayerComponent);

	ApproachComponent = ApproachAction->GetApproach();
	return bApproach;
}

void USitDownStandUpFlowNode::DoStandUp()
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();
	if (!NonPlayerComponent.IsValid())
	{
		return;
	}
	State = ESitDownStandUpFlowExecutionState::StandUp;
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = rand();
	LatentInfo.Linkage = 0;
	LatentInfo.ExecutionFunction = TEXT("IsStanding");
	NonPlayerComponent->PlayAnimationMontage(StandUp, StandUpSection, 0, LatentInfo);

	FTimerHandle Handle;
	FTimerDelegate Delegate;
	Delegate.BindLambda([NonPlayerComponent, this]
	{
		NonPlayerComponent->SetAnimationOverride(nullptr, true);

		if (ApproachComponent.IsValid())
		{
			ApproachComponent->SetOccupied(false);
		}
	});
	GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, 0.1, false);
}

void USitDownStandUpFlowNode::ApplyIdle()
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();

	if (!NonPlayerComponent.IsValid())
	{
		return;
	}

	State = ESitDownStandUpFlowExecutionState::Idle;
	if (ApproachComponent.IsValid())
	{
		ApproachComponent->SetOccupied(true);
	}

	UCapsuleComponent* CapsuleComponent = NonPlayerComponent->GetOwner()->FindComponentByClass<UCapsuleComponent>();
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	NonPlayerComponent->SetAnimationOverride(Idle, true);
}

void USitDownStandUpFlowNode::IsSitting()
{
	ApplyIdle();
	TriggerOutput(TEXT("Idle"));
}

void USitDownStandUpFlowNode::IsStanding()
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();
	if (NonPlayerComponent.IsValid())
	{
		State = ESitDownStandUpFlowExecutionState::None;

		NonPlayerComponent->GetOwner()->FindComponentByClass<UCapsuleComponent>()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		NonPlayerComponent->GetOwner()->FindComponentByClass<UCapsuleComponent>()->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
	}

	TriggerOutput(TEXT("Complete"), true);
}

void USitDownStandUpFlowNode::Approached()
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();
	if (!NonPlayerComponent.IsValid())
	{
		return;
	}

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = rand();
	LatentInfo.Linkage = 0;
	LatentInfo.ExecutionFunction = TEXT("IsSitting");

	ApproachComponent->SetOccupied(true);

	NonPlayerComponent->PlayAnimationMontage(SitDown, SitDownSection, 0, LatentInfo);

	State = ESitDownStandUpFlowExecutionState::SitDown;

	FTimerHandle Handle;
	FTimerDelegate Delegate;
	Delegate.BindLambda([NonPlayerComponent, this]
	{
		NonPlayerComponent->SetAnimationOverride(Idle, true);
	});
	GetWorld()->GetTimerManager().SetTimer(Handle, Delegate, 0.1, false);
}
