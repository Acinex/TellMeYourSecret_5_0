// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "UObject/Object.h"
#include "TMYSButton.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UTMYSButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetText(FText InText);

protected:
	UPROPERTY(meta=(BindWidget), BlueprintReadOnly)
	UCommonTextBlock* TextBlock;

	UPROPERTY(EditInstanceOnly)
	FText Text;

	virtual void NativePreConstruct() override;
};
