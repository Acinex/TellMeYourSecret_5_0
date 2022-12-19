// Copyright Acinex Games 2020


#include "QuestFlowAsset.h"

#include "QuestManager.h"
#include "Kismet/GameplayStatics.h"

void UQuestFlowAsset::StartFlow()
{
	UQuestManager* QuestManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UQuestManager>();
	if (QuestManager)
	{
		QuestManager->ActivateQuest(this);
	}

	Super::StartFlow();
}

void UQuestFlowAsset::FinishFlow(const EFlowFinishPolicy InFinishPolicy, const bool bRemoveInstance /*= true*/)
{
	UQuestManager* QuestManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UQuestManager>();
	if (QuestManager)
	{
		QuestManager->CompleteQuest(this);
	}
	
	Super::FinishFlow(InFinishPolicy, bRemoveInstance);
}

void UQuestFlowAsset::OnLoad_Implementation()
{
	UQuestManager* QuestManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UQuestManager>();
	if (QuestManager)
	{
		QuestManager->LoadQuest(Cast<UQuestFlowAsset>(this));
	}
}
