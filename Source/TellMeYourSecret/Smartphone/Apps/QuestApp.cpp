#include "QuestApp.h"

#include "TellMeYourSecret/Characters/CharacterData.h"
#include "TellMeYourSecret/Characters/ReputationSystem.h"
#include "Components/ListView.h"
#include "TellMeYourSecret/Quests/QuestFlowAsset.h"
#include "TellMeYourSecret/Quests/QuestManager.h"
#include "TellMeYourSecret/Smartphone/CharacterIconWidget.h"
#include "TellMeYourSecret/UMG/Colors.h"

void UQuestApp::NativeConstruct()
{
	Super::NativeConstruct();

	Characters->SetListItems(ReputationSystem->GetKnownCharacters());
	Characters->SetSelectedItem(Selected);
}

void UQuestApp::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	QuestManager = GetGameInstance()->GetSubsystem<UQuestManager>();
	ReputationSystem = GetGameInstance()->GetSubsystem<UReputationSystem>();

	Characters->OnItemSelectionChanged().AddLambda([this](UObject* Item)
	{
		if (Item)
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Item->GetName())
		Selected = Cast<UCharacterData>(Item);
		for (auto DisplayedEntryWidget : Characters->GetDisplayedEntryWidgets())
		{
			UCharacterIconWidget* CharacterIconWidget = Cast<UCharacterIconWidget>(DisplayedEntryWidget);
			CharacterIconWidget->SetSelected(CharacterIconWidget->GetCharacterData() == Selected);
		}

		if (Selected)
		{
			//QuestManager->GetActiveQuests(Selected->Identifier, ActiveQuests);
		}
		else
		{
			// ActiveQuests.Empty();
		}
	});
}

FText UQuestApp::GetMainQuestTitle() const
{
	const UQuestFlowAsset* ActiveMainQuest = QuestManager->GetActiveMainQuest();
	if (ActiveMainQuest)
	{
		return ActiveMainQuest->GetTitle();
	}

	return NSLOCTEXT("Quest", "Quest.Main.None.Title", "No quest yet");
}

FLinearColor UQuestApp::GetMainQuestColor() const
{
	const UQuestFlowAsset* ActiveMainQuest = QuestManager->GetActiveMainQuest();
	if (ActiveMainQuest && ActiveMainQuest->IsCompleted())
	{
		return Colors::Quests::Done;
	}

	return Colors::White;
}

FText UQuestApp::GetSideQuestTitle() const
{
	return NSLOCTEXT("Quest", "Quest.Side.None.Title", "No quest yet");
}

FLinearColor UQuestApp::GetSideQuestColor() const
{
	return Colors::White;
}

ESlateVisibility UQuestApp::ContentVisibility() const
{
	if (Selected)
	{
		return ESlateVisibility::Visible;
	}

	return ESlateVisibility::Hidden;
}
