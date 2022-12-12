// Copyright Acinex Games 2020

#include "ShowDialogueFlowNode.h"

#include "FlowSubsystem.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "TellMeYourSecret/Characters/UI/DialogueContainer.h"
#include "TellMeYourSecret/Characters/Util/LipSyncExecutor.h"
#include "TellMeYourSecret/Characters/Util/LipSyncUtil.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Log.h"

const FString UShowDialogueFlowNode::Continue = TEXT("Continue");

UShowDialogueFlowNode::UShowDialogueFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Dialogue");
#endif
	RefreshOutputs();
}

void UShowDialogueFlowNode::ExecuteInput(const FName& PinName)
{
	CharacterComponent = FindCharacter();

	if (!CharacterComponent.IsValid())
	{
		return;
	}

	UDialogueContainer* DialogueContainer = CharacterComponent->GetDialogueWidget();
	if (!DialogueContainer)
	{
		return LogError("Character has no Dialogue Container");
	}

	AActor* Partner = FindActor(PartnerIdentityTags);
	if (Partner)
	{
		CharacterComponent->SetLookAtTarget(Partner->FindComponentByClass<USkeletalMeshComponent>());
		PartnerCharacterComponent = Partner->FindComponentByClass<UCharacterComponent>();
		if (PartnerCharacterComponent.IsValid())
		{
			PartnerCharacterComponent->SetLookAtTarget(CharacterComponent->GetOwner()->FindComponentByClass<USkeletalMeshComponent>());
		}
	}

	UE_LOG(LogTellMeYourSecret, Log, TEXT("Set Speaker %s"), *CharacterComponent->CharacterData->Name)
	DialogueContainer->SetDialogue(CharacterComponent->CharacterData, Text, Answers);

	LipSyncExecutor = NewObject<ULipSyncExecutor>(this, TEXT("LipSyncExecutor"));
	LipSyncExecutor->Start(CharacterComponent.Get(), {AudioTrack.Get(), AudioDelay, Syllables, LipSyncDelay, Montage.Get(), StartSectionName});

	TWeakObjectPtr<UShowDialogueFlowNode> SelfWeakPtr(this);

	DialogueContainer->OnOptionChosen.AddWeakLambda(this, [SelfWeakPtr](const int32 ChosenOption)
	{
		if (SelfWeakPtr.IsValid())
		{
			SelfWeakPtr->GetWorld()->GetTimerManager().ClearAllTimersForObject(SelfWeakPtr.Get());

			SelfWeakPtr->Stop();
			SelfWeakPtr->CharacterComponent->SetLookAtTarget(nullptr);

			if (SelfWeakPtr->PartnerCharacterComponent.IsValid())
			{
				SelfWeakPtr->PartnerCharacterComponent->SetLookAtTarget(nullptr);
			}

			if (ChosenOption == -1)
			{
				SelfWeakPtr->TriggerOutput(Continue, true);
			}
			else
			{
				SelfWeakPtr->TriggerOutput(SelfWeakPtr->OutputPins[ChosenOption].PinName, true);
			}
		}
	});
}

#if WITH_EDITOR
void UShowDialogueFlowNode::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UShowDialogueFlowNode, Answers))
	{
		RefreshOutputs();
		OnReconstructionRequested.ExecuteIfBound();
	}

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UShowDialogueFlowNode, Text))
	{
		RefreshSyllables();
		OnReconstructionRequested.ExecuteIfBound();
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

FString UShowDialogueFlowNode::GetNodeDescription() const
{
	return Super::GetNodeDescription() + LINE_TERMINATOR + Text.ToString();
}

void UShowDialogueFlowNode::FixNode(UEdGraphNode* NewGraph)
{
	RefreshOutputs();
}

void UShowDialogueFlowNode::RefreshSyllables()
{
	FLipSyncUtil::CreateSyllables(Text, Syllables);
}
#endif

void UShowDialogueFlowNode::RefreshOutputs()
{
	OutputPins.Empty();

	if (!Answers.Num())
	{
		OutputPins.Add({Continue});
	}

	for (FText Answer : Answers)
	{
		OutputPins.Add({Answer.ToString(), FText::FromString(FString::FromInt(OutputPins.Num())), Answer.ToString()});
	}
}

void UShowDialogueFlowNode::Stop() const
{
	LipSyncExecutor->Stop();
}

void UShowDialogueFlowNode::PreloadContent()
{
	if (!Montage.IsNull())
	{
		// ReSharper disable once CppExpressionWithoutSideEffects
		Montage.LoadSynchronous();
	}
	if (!AudioTrack.IsNull())
	{
		// ReSharper disable once CppExpressionWithoutSideEffects
		AudioTrack.LoadSynchronous();
	}
}
