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
	UPROPERTY(EditInstanceOnly, meta=(FlowOutput))
	FText Title;
	UPROPERTY(EditInstanceOnly, meta=(FlowOutput))
	FText Description;
	UPROPERTY(EditInstanceOnly, meta=(FlowOutput))
	EQuestType Type;
	UPROPERTY(SaveGame, meta=(FlowOutput))
	bool bFollowed;
	UPROPERTY(SaveGame)
	bool bCompleted;

	virtual void OnLoad_Implementation() override;
};
