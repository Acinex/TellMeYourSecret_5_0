#pragma once
#include "CommonActivatableWidget.h"
#include "UIBase.generated.h"

class UCommonActivatableWidgetStack;

UCLASS()
class TELLMEYOURSECRET_API UUIBase: public UCommonActivatableWidget
{
    GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void PushMenu(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	UFUNCTION(BlueprintCallable)
	UCommonActivatableWidget* PushPrompt(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);


protected:
	UPROPERTY(meta=(BindWidget))
	UCommonActivatableWidgetStack* MenuStack;
	UPROPERTY(meta=(BindWidget))
	UCommonActivatableWidgetStack* PromptStack;
};
