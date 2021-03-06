// Copyright Acinex Games 2020

#include "AbstractMontageFlowNode.h"
#include "Animation/AnimInstance.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "TellMeYourSecret/Log.h"

UAbstractMontageFlowNode::UAbstractMontageFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Animation");
#endif
	OutputPins.Add({TEXT("Complete"), TEXT("Will be executed when the animation is completed")});
}

#if WITH_EDITOR
FString UAbstractMontageFlowNode::GetNodeDescription() const
{
	if (Montage.IsNull())
	{
		return TEXT("No Animation Montage selected!");
	}

	return Montage.GetAssetName().Append("\n").Append(Super::GetNodeDescription());
}

bool UAbstractMontageFlowNode::IsParametersValid() const
{
	return !Montage.IsNull();
}
#endif

void UAbstractMontageFlowNode::Cleanup()
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();
	if (!IsValid(NonPlayerComponent.Get()) || !Montage.IsValid())
	{
		return;
	}

	FLatentActionManager& LatentActionManager = GetWorld()->GetLatentActionManager();
	LatentActionManager.RemoveActionsForObject(this);
	NonPlayerComponent->PauseAnimationMontage();
}

void UAbstractMontageFlowNode::OnLoad_Implementation()
{
	PlayAnimation();
}

void UAbstractMontageFlowNode::OnSave_Implementation()
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();
	if (!IsValid(NonPlayerComponent.Get()) || !Montage.IsValid())
	{
		return;
	}

	if (const UAnimInstance* AnimInstance = NonPlayerComponent->GetAnimInstance<UAnimInstance>())
	{
		Position = AnimInstance->GetActiveMontageInstance()->GetPosition();
	}
}

void UAbstractMontageFlowNode::OnAnimNotify(const FName Name)
{
}

void UAbstractMontageFlowNode::AnimationFinished()
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();

	if (!NonPlayerComponent.IsValid())
	{
		return;
	}

	if (UAnimInstance* AnimInstance = NonPlayerComponent->GetAnimInstance<UAnimInstance>())
	{
		AnimInstance->OnPlayMontageNotifyBegin.RemoveAll(this);
	}

	OnComplete();
}

void UAbstractMontageFlowNode::PreloadContent()
{
	if(!Montage.IsNull())
	{
		// ReSharper disable once CppExpressionWithoutSideEffects
		Montage.LoadSynchronous();
	}
}

void UAbstractMontageFlowNode::PlayAnimation()
{	
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();
	if (!IsValid(NonPlayerComponent.Get()) || !IsValid(Montage.LoadSynchronous()))
	{
		AddStatusReport(TEXT("No Actor or Montage"));
		return Finish();
	}

	FLatentActionInfo LatentInfo;
	LatentInfo.ExecutionFunction = TEXT("AnimationFinished");
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = rand();
	LatentInfo.Linkage = 0;

	NonPlayerComponent->PlayAnimationMontage(Montage.Get(), Position == -1.0F ? StartSectionName : NAME_None, Position, LatentInfo);
	UE_LOG(LogTellMeYourSecret, Log, TEXT("Playing %s"), *Montage->GetName())

	if (UAnimInstance* AnimInstance = NonPlayerComponent->GetAnimInstance<UAnimInstance>())
	{
		if (const FAnimMontageInstance* Instance = AnimInstance->MontageInstances[AnimInstance->MontageInstances.Num() - 1])
		{
			MontageInstanceID = Instance->GetInstanceID();
			AnimInstance->OnPlayMontageNotifyBegin.AddUniqueDynamic(this, &UAbstractMontageFlowNode::OnPlayMontageNotifyBegin);
		}
		else
		{
			LogError("No matching AnimMontageInstance found");
		}
	}
}

void UAbstractMontageFlowNode::Stop()
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();
	if (!IsValid(NonPlayerComponent.Get()) || !IsValid(Montage.LoadSynchronous()))
	{
		Finish();
		return;
	}

	NonPlayerComponent->StopAnimationMontage(Montage.Get());
	if (UAnimInstance* AnimInstance = NonPlayerComponent->GetAnimInstance<UAnimInstance>())
	{
		AnimInstance->OnPlayMontageNotifyBegin.RemoveAll(this);
	}
}

void UAbstractMontageFlowNode::OnPlayMontageNotifyBegin(const FName Name, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	UE_LOG(LogTellMeYourSecret, Log, TEXT("Notify %s from %i Watching on %i"), *Name.ToString(), BranchingPointPayload.MontageInstanceID, MontageInstanceID)
	if (BranchingPointPayload.MontageInstanceID == MontageInstanceID)
	{
		OnAnimNotify(Name);
	}
}
