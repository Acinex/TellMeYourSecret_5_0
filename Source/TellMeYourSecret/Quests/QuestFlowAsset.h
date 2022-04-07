// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "FlowAsset.h"
#include "QuestType.h"
#include "QuestFlowAsset.generated.h"

/**
 * 
 */
UCLASS(DisplayName=Quest)
class TELLMEYOURSECRET_API UQuestFlowAsset : public UFlowAsset
{
	GENERATED_BODY()

	friend class UQuestManager;

public:
	virtual void StartFlow() override;

	virtual void FinishFlow(const EFlowFinishPolicy InFinishPolicy) override;

	UFUNCTION(BlueprintPure)
	FText GetTitle() const { return Title; }

	UFUNCTION(BlueprintPure)
	FText GetDescription() const { return Description; }

	UFUNCTION(BlueprintPure)
	bool IsCompleted() const { return bCompleted; }

protected:
	UPROPERTY(EditInstanceOnly)
	FText Title;
	UPROPERTY(EditInstanceOnly)
	FText Description;
	UPROPERTY(EditInstanceOnly)
	EQuestType Type;
	UPROPERTY(SaveGame)
	bool bFollowed;
	UPROPERTY(SaveGame)
	bool bCompleted;

	virtual void OnLoad_Implementation() override;
};
