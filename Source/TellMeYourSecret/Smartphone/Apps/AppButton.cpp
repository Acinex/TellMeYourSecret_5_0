#include "AppButton.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/UniformGridSlot.h"
#include "Engine/Texture.h"
#include "TellMeYourSecret/Smartphone/Smartphone.h"

void UAppButton::SetShowNotification(const bool InShowNotification)
{
	ShowNotification = InShowNotification;
	if (ShowNotification)
	{
		NotificationIcon->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		NotificationIcon->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UAppButton::SetApp(UAppWidget* InApp)
{
	App = InApp;

	UUniformGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(this);
	if (!GridSlot)
	{
		return;
	}

	GridSlot->SetColumn(App->GetColumn());
	GridSlot->SetRow(App->GetRow());

	FSlateBrush Brush;
	Brush.SetResourceObject(App->GetIcon());
	Brush.SetImageSize(FVector2D(60.0, 60.0));
	Brush.DrawAs = ESlateBrushDrawType::Image;

	Button->WidgetStyle.Normal  = Brush;
	Button->WidgetStyle.Hovered = Brush;
	Button->WidgetStyle.Pressed = Brush;
	Button->SetVisibility(ESlateVisibility::Visible);
}

void UAppButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button->OnClicked.AddDynamic(this, &UAppButton::OpenApp);
}

void UAppButton::NativeConstruct()
{
	Button->SetVisibility(ESlateVisibility::Hidden);
	NotificationIcon->SetVisibility(ESlateVisibility::Hidden);
}

void UAppButton::OpenApp()
{
	USmartphone* Smartphone = UGameplayStatics::GetGameInstance(this)->GetSubsystem<USmartphone>();

	if (!Smartphone || !App)
	{
		return;
	}

	Smartphone->OpenApp(App);
}
