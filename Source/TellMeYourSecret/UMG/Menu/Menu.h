#pragma once
#include "Blueprint/UserWidget.h"
#include "Menu.generated.h"

class UButton;
class UMainMenuContainer;

UCLASS(BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API UMenu : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* PlayButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* GameButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* CustomizationButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* OptionsButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* AboutButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* QuitButton;

    UPROPERTY(BlueprintReadOnly, Transient, meta=(BindWidgetAnim))
    UWidgetAnimation* GameMenuAnimation;
    UPROPERTY(BlueprintReadOnly, Transient, meta=(BindWidgetAnim))
    UWidgetAnimation* OptionsMenuAnimation;
    UPROPERTY(BlueprintReadOnly, Transient, meta=(BindWidgetAnim))
    UWidgetAnimation* AboutMenuAnimation;
    UPROPERTY(BlueprintReadOnly, Transient, meta=(BindWidgetAnim))
    UWidgetAnimation* CustomizationMenuAnimation;


    UPROPERTY(Transient)
    UWidgetAnimation* CurrentAnimation;

    UFUNCTION(BlueprintPure)
    FText PlayButtonText() const;

private:

    UFUNCTION()
    void Play();
    UFUNCTION()
    void ShowGame();
    UFUNCTION()
    void ShowCustomization();
    UFUNCTION()
    void ShowOptions();
    UFUNCTION()
    void ShowAbout();
    UFUNCTION()
    void Quit();

    void ToggleMenu(UWidgetAnimation* Animation);

    UFUNCTION()
    void CloseActiveMenu();
};