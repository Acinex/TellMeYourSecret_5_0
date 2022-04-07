// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual TSharedRef<SWidget, ESPMode::ThreadSafe> RebuildWidget() override;

	void SetText(const FText InText);

	UFUNCTION()
	// ReSharper disable once CppMemberFunctionMayBeConst
	FText GetText() { return Text; }

	void SetActor(AActor* InActor) { Actor = InActor; }

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	AActor* Actor;

	UPROPERTY()
	UTextBlock* TextBlock;
	FText       Text;
};
