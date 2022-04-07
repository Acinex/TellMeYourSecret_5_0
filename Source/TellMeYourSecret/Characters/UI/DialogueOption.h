// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "DialogueContainer.h"
#include "Blueprint/UserWidget.h"
#include "DialogueOption.generated.h"

/**
* 
*/
UCLASS(Blueprintable, BlueprintType)
class TELLMEYOURSECRET_API UDialogueOption : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	void SetText(const FText& InText) const;
	void SetDialogueContainer(UDialogueContainer* InDialogueContainer);

	int32 GetIndex() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	UButton* Button;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
	URichTextBlock* Text;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn))
	int32 Index;

private:
	UPROPERTY()
	UDialogueContainer* DialogueContainer;

	UFUNCTION()
	void Choose();
};
