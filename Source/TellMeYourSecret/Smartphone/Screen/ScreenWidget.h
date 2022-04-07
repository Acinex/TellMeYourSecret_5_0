#pragma once

#include "Blueprint/UserWidget.h"
#include "ScreenWidget.generated.h"

class UAppButton;
class UUniformGridPanel;
class USmartphone;
class UButton;
class UScaleBox;
class UCanvasPanel;
class UAppWidget;

UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UScreenWidget : public UUserWidget
{
    GENERATED_BODY()
public:

    UFUNCTION(BlueprintCallable)
    void ShowApp(UAppWidget* App);

    UFUNCTION(BlueprintCallable)
    void HideApp(UAppWidget* App);

    UFUNCTION(BlueprintCallable)
    void AddApp(UAppWidget* App);

    virtual void NativeConstruct() override;
    virtual void NativePreConstruct() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UPanelWidget* Root;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UPanelWidget* ScaleBox;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UUniformGridPanel* AppGrid;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* BackButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* HomeButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* OptionsButton;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UAppButton> AppButtonClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USmartphone* Smartphone;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UAppWidget* OpenApp;

    UFUNCTION(BlueprintCallable)
    void ShowNotification(UAppWidget* App);

    UFUNCTION()
    void Home();
    UFUNCTION()
    void Back();
    UFUNCTION()
    void Options();

private:
    UPROPERTY()
    TArray<UAppWidget*> Apps;

    UAppButton* FindAppButton(UAppWidget* App) const;
};
