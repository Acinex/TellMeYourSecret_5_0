// Copyright Acinex Games 2020.

#include "QuestManager.h"
#include "QuestFlowAsset.h"
#include "QuestType.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/Smartphone/Smartphone.h"
#include "TellMeYourSecret/Smartphone/Apps/QuestApp.h"


void UQuestManager::ActivateQuest(UQuestFlowAsset* Quest)
{
	ActiveQuests.Emplace(Quest);

	UE_LOG(LogTellMeYourSecret, Log, TEXT("Activate quest %s"), *Quest->Title.ToString())

	Quest->bFollowed = true;
	const USmartphone* Smartphone = GetGameInstance()->GetSubsystem<USmartphone>();
	Smartphone->OnNotification.Broadcast(Smartphone->GetQuestApp());
}

void UQuestManager::LoadQuest(UQuestFlowAsset* Quest)
{
	UE_LOG(LogTellMeYourSecret, Log, TEXT("Load quest %s"), *Quest->Title.ToString())
	ActiveQuests.Emplace(Quest);
}

void UQuestManager::CompleteQuest(UQuestFlowAsset* Quest)
{
	Quest->bCompleted = true;
	const USmartphone* Smartphone = GetGameInstance()->GetSubsystem<USmartphone>();
	Smartphone->OnNotification.Broadcast(Smartphone->GetQuestApp());
}

UQuestFlowAsset* UQuestManager::GetActiveMainQuest() const
{
	const auto Match = ActiveQuests.FindByPredicate([](const UQuestFlowAsset* Quest)
	{
		return Quest->bFollowed && Quest->Type == EQuestType::Main;
	});

	if (Match)
	{
		return *Match;
	}

	return nullptr;
}
