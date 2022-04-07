// Copyright Acinex Games 2020

#include "DialogueContainer.h"

#include "Components/Button.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "DialogueOption.h"
#include "TellMeYourSecret/Characters/CharacterData.h"
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"
#include "TellMeYourSecret/Model/Save/Settings.h"

void UDialogueContainer::SetDialogue(UCharacterData* Character, const FText Message, const TArray<FText> Answers)
{
	Options = Answers;

	SpeakerName->SetVisibility(ESlateVisibility::Visible);
	SpeakerName->SetText(FText::FromString(Character->Name));
	SpeakerName->SetColorAndOpacity(FSlateColor(Character->SpeakerColor));

	DialogueText->SetText(Message);
	ShowOptions();
	AddToViewport();
	FInputModeGameAndUI Data = FInputModeGameAndUI();
	Data.SetHideCursorDuringCapture(true);
	GetOwningPlayer()->SetInputMode(Data);
	GetOwningPlayer()->bShowMouseCursor = true;
}

void UDialogueContainer::ChooseDialogueOption(const int32 Index)
{
	RemoveFromParent();
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	GetOwningPlayer()->bShowMouseCursor = false;

	OnOptionChosen.Broadcast(Index);
}

void UDialogueContainer::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());

	DialogueClickToContinue->OnClicked.AddDynamic(this, &UDialogueContainer::Continue);

	TArray<UDialogueOption*> DialogueOptions = {Option0, Option1, Option2, Option3, Option4, Option5};

	for (UDialogueOption* Option : DialogueOptions)
	{
		Option->SetDialogueContainer(this);
	}
}

void UDialogueContainer::ShowOptions() const
{
	TArray<UDialogueOption*> DialogueOptions = {Option0, Option1, Option2, Option3, Option4, Option5};

	if (Options.Num() == 0)
	{
		DialogueOptionsContainer->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	DialogueOptionsContainer->SetVisibility(ESlateVisibility::Visible);

	for (UDialogueOption* Option : DialogueOptions)
	{
		const int32 Index = Option->GetIndex();

		const bool bVisible = Options.Num() > Index;
		if (bVisible)
		{
			Option->SetText(FormatText(Options[Index]));
		}

		Option->SetVisibility(!bVisible ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	}
}

void UDialogueContainer::Continue()
{
	if (Options.Num())
	{
		return;
	}

	ChooseDialogueOption(-1);
}

FText UDialogueContainer::FormatText(const FText Input) const
{
	FFormatNamedArguments Arguments;

	Arguments.Add(TEXT("PlayerName"), FFormatArgumentValue(FText::FromString(GameInstance->GetSettings()->PlayerName)));
	return FText::Format(Input, Arguments);
}
