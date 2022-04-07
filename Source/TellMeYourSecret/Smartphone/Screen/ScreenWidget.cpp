#include "ScreenWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/PanelWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "TellMeYourSecret/Smartphone/Smartphone.h"
#include "TellMeYourSecret/Smartphone/Apps/AppButton.h"
#include "TellMeYourSecret/Smartphone/Apps/AppWidget.h"
#include "TellMeYourSecret/Log.h"

void UScreenWidget::ShowApp(UAppWidget* App)
{
    ScaleBox->ClearChildren();
    ScaleBox->AddChild(App);
    ScaleBox->SetVisibility(ESlateVisibility::Visible);

    OpenApp = App;

    UAppButton* AppButton = FindAppButton(App);
    if (!AppButton)
    {
        return;
    }

    AppButton->SetShowNotification(false);
}

void UScreenWidget::HideApp(UAppWidget* App)
{
    ScaleBox->ClearChildren();
    OpenApp = nullptr;
    ScaleBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UScreenWidget::AddApp(UAppWidget* App)
{
    Apps.Add(App);
}

void UScreenWidget::NativeConstruct()
{
    Super::NativeConstruct();

    Smartphone = UGameplayStatics::GetGameInstance(this)->GetSubsystem<USmartphone>();
    Smartphone->OnNotification.AddDynamic(this, &UScreenWidget::ShowNotification);

    BackButton->OnClicked.AddDynamic(this, &UScreenWidget::Back);
    HomeButton->OnClicked.AddDynamic(this, &UScreenWidget::Home);
}

void UScreenWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    for (UAppWidget* App : Apps)
    {
        UAppButton* AppButton = FindAppButton(App);
        if (!AppButton)
        {
            continue;
        }
        AppButton->SetApp(App);
    }
}

void UScreenWidget::ShowNotification(UAppWidget* App)
{
    UAppButton* AppButton = FindAppButton(App);
    if (!AppButton)
    {
        return;
    }

    AppButton->SetShowNotification(true);
}

void UScreenWidget::Home()
{
    if (OpenApp)
    {
        Smartphone->Home();
        OpenApp = nullptr;
    }
    else
    {
        Smartphone->Back();
    }
}

void UScreenWidget::Back()
{
    Smartphone->Back();
}

void UScreenWidget::Options()
{
}

UAppButton* UScreenWidget::FindAppButton(UAppWidget* App) const
{
    if (!App)
    {
        return nullptr;
    }

    for (UWidget* Child : AppGrid->GetAllChildren())
    {
        UUniformGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(Child);

        if (App->GetRow() == GridSlot->Row && App->GetColumn() == GridSlot->Column)
        {
            return Cast<UAppButton>(Child);
        }
    }

    return nullptr;
}
