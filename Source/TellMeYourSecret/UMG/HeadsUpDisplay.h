#pragma once
#include "Blueprint/UserWidget.h"
#include "HeadsUpDisplay.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API UHeadsUpDisplay : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void ShowNotification(FSlateBrush Image);
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void HideNotification();
};
