#pragma once
#include "AppWidget.h"
#include "Blueprint/UserWidget.h"

#include "AppButton.generated.h"

class UButton;
class UImage;
UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UAppButton : public UUserWidget
{
    GENERATED_BODY()
public:
    void SetShowNotification(const bool InShowNotification);
    void SetApp(UAppWidget* InApp);

    virtual void NativeOnInitialized() override;

    virtual void NativeConstruct() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* Button;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UImage* NotificationIcon;

private:
    bool ShowNotification;
    UPROPERTY()
    UAppWidget* App;
    UFUNCTION()
    void OpenApp();
};
