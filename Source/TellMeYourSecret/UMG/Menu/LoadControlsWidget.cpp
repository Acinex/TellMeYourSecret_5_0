// Copyright Acinex Games 2020

#include "LoadControlsWidget.h"

#include "SaveGameWidget.h"
#include "Components/PanelWidget.h"
#include "TellMeYourSecret/GameInstances/SaveManager.h"
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"
#include "TellMeYourSecret/Model/Save/Settings.h"

ULoadControlsWidget::ULoadControlsWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

void ULoadControlsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Reload();
	USaveManager* SaveManager = GetGameInstance()->GetSubsystem<USaveManager>();
	SaveManager->OnSavesUpdated.AddDynamic(this, &ULoadControlsWidget::Reload);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ULoadControlsWidget::Reload()
{
	GameSlots->ClearChildren();

	const UTellMeYourSecretGameInstance* Instance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());

	USaveGameWidget* CreateNew = CreateWidget<USaveGameWidget>(GetOwningPlayer(), SaveGameWidgetClass);
	GameSlots->AddChild(CreateNew);

	for (const auto GameInfo : Instance->GetSettings()->SaveGameInfos)
	{
		USaveGameWidget* SaveGameWidget = CreateWidget<USaveGameWidget>(GetOwningPlayer(), SaveGameWidgetClass);
		SaveGameWidget->SaveGameInfo    = GameInfo;
		GameSlots->AddChild(SaveGameWidget);
	}
}
