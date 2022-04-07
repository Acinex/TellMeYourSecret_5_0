#pragma once

#include "AppWidget.h"
#include "QuestApp.generated.h"

class UQuestManager;
class UReputationSystem;
class UCharacterData;
class UListView;

UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UQuestApp : public UAppWidget
{
	GENERATED_BODY()
public:
	virtual int GetRow() const override { return 0; }
	virtual int GetColumn() const override { return 0; }

	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta=(BindWidget))
	UListView* Characters;

	UFUNCTION(BlueprintPure)
	FText GetMainQuestTitle() const;
	UFUNCTION(BlueprintPure)
	FLinearColor GetMainQuestColor() const;

	UFUNCTION(BlueprintPure)
	FText GetSideQuestTitle() const;
	UFUNCTION(BlueprintPure)
	FLinearColor GetSideQuestColor() const;

	UFUNCTION(BlueprintPure)
	ESlateVisibility ContentVisibility() const;

private:
	UPROPERTY()
	UCharacterData* Selected;

	UPROPERTY()
	UQuestManager* QuestManager;
	UPROPERTY()
	UReputationSystem* ReputationSystem;
};
