// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "ButtonGroupWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOptionClicked, int8);

class UCheckBox;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UButtonGroupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	void Select(FText Option);

	void SetSelected(int8 Index);

	FOptionClicked OnOptionClicked;

protected:
	UPROPERTY(EditInstanceOnly)
	TArray<FText> Options;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Clear();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddButton(UCheckBox* Button);

private:
	UPROPERTY()
	TArray<UCheckBox*> CheckBoxes;
};

UCLASS()
class UClickProxy : public UObject
{
	GENERATED_BODY()
public:
	FText Option;
	UPROPERTY()
	TWeakObjectPtr<UButtonGroupWidget> Group;

	UFUNCTION()
	// ReSharper disable once CppMemberFunctionMayBeConst
	void Broadcast(bool bIsChecked)
	{
		if (Group.IsValid())
		{
			Group->Select(Option);
		}
	}
};
