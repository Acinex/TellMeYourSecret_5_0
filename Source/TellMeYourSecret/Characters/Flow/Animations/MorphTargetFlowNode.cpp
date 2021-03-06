// Copyright Acinex Games 2020

#include "MorphTargetFlowNode.h"

#include "FlowAsset.h"
#include "TellMeYourSecret/TellMeYourSecretGameSettings.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "TellMeYourSecret/Characters/Util/MorphTargetExecutor.h"

UMorphTargetFlowNode::UMorphTargetFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Animation");
#endif

	OutputPins.Add({TEXT("Complete"), TEXT("Will be executed when the animation is completed")});
}

void UMorphTargetFlowNode::ExecuteInput(const FName& PinName)
{
	const TWeakObjectPtr<UNonPlayerComponent> NonPlayerComponent = FindNonPlayer();

	if (!NonPlayerComponent.IsValid())
	{
		return;
	}

	if (bClearMorphTargets)
	{
		NonPlayerComponent->ClearMorphTargets();
	}

	Executor = NewObject<UMorphTargetExecutor>(this, TEXT("Executor"));
	Executor->OnStepFinished.AddDynamic(this, &UMorphTargetFlowNode::FinishStep);
	Counter = MorphTargets.Num();

	for (const auto MorphTargetChange : MorphTargets)
	{
		Executor->AddMorphTargetChange(NonPlayerComponent.Get(), MorphTargetChange);
	}

	TriggerFirstOutput(false);
	if (!MorphTargets.Num())
	{
		Counter = 1;
		FinishStep();
	}
}

void UMorphTargetFlowNode::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UMorphTargetFlowNode, Title) && bUsedTemplate)
	{
		static UTellMeYourSecretGameSettings* TellMeYourSecretGameSettings = UTellMeYourSecretGameSettings::Get();
		if (TellMeYourSecretGameSettings->MorphTargetTemplates.IsNull())
		{
			return;
		}

		const UDataTable* DataTable = TellMeYourSecretGameSettings->MorphTargetTemplates.LoadSynchronous();
		static const FString ContextString = "UMorphTargetFlowNode";

		if (const FLetterMorphTarget* Row = DataTable->FindRow<FLetterMorphTarget>(FName(Title), ContextString))
		{
			MorphTargets = TSet(Row->MorphTargetChanges);
			bUsedTemplate = true;
		}

		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Property was changed: %s"), *PropertyChangedEvent.GetPropertyName().ToString())

	static TArray Properties = {FName("Name"), FName("Value"), FName("Time"), FName("Steps"), FName("MorphTargets")};

	if (Properties.Contains(PropertyChangedEvent.GetPropertyName()))
	{
		static UTellMeYourSecretGameSettings* TellMeYourSecretGameSettings = UTellMeYourSecretGameSettings::Get();
		if (TellMeYourSecretGameSettings->MorphTargetTemplates.IsNull())
		{
			bUsedTemplate = false;
			return;
		}

		const UDataTable* DataTable = TellMeYourSecretGameSettings->MorphTargetTemplates.LoadSynchronous();
		static const FString ContextString = "UMorphTargetFlowNode";

		if (const FLetterMorphTarget* Row = DataTable->FindRow<FLetterMorphTarget>(FName(Title), ContextString))
		{
			if (MorphTargets.Num() != Row->MorphTargetChanges.Num())
			{
				bUsedTemplate = false;
				return;
			}

			bool bSame = true;
			int Index = 0;
			for (FMorphTargetChange MorphTarget : MorphTargets)
			{
				if (MorphTarget != Row->MorphTargetChanges[Index])
				{
					bSame = false;
					break;
				}
				Index++;
			}

			bUsedTemplate = bSame;
		}
	}
}

#if WITH_EDITOR
FString UMorphTargetFlowNode::GetNodeDescription() const
{
	return Super::GetNodeDescription() + LINE_TERMINATOR + Title + LINE_TERMINATOR + (bUsedTemplate ? TEXT("Uses Template") : TEXT("Is Customized"));
}

bool UMorphTargetFlowNode::IsParametersValid() const
{
	return MorphTargets.Num() > 0;
}

FString UMorphTargetFlowNode::GetStatusString() const
{
	return Counter > 0 ? FString::FromInt(Counter) : FString();
}
#endif

void UMorphTargetFlowNode::FinishStep()
{
	Counter--;
	if (Counter == 0)
	{
		return TriggerOutput(TEXT("Complete"), true);
	}
}
