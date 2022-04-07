// Copyright Acinex Games 2020.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestManager.generated.h"

class UQuestFlowAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestUpdate, UQuestFlowAsset*, Quest);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQuestActivated, UQuestFlowAsset*, Quest);

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UQuestManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void ActivateQuest(UQuestFlowAsset* Quest);
	
	void LoadQuest(UQuestFlowAsset* Quest);
	
	void CompleteQuest(UQuestFlowAsset* Quest);

	UFUNCTION(BlueprintCallable)
	UQuestFlowAsset* GetActiveMainQuest() const;

private:
	UPROPERTY()
	TArray<UQuestFlowAsset*> ActiveQuests;
};
