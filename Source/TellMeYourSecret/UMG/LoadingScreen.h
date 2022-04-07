#pragma once
#include "Blueprint/UserWidget.h"
#include "LoadingScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadFinish);

UCLASS(Blueprintable)
class ULoadingScreen : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent)
    void UpdateLoadingProgress(const float Progress);
};
