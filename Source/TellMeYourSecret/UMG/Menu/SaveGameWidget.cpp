// Copyright Acinex Games 2020

#include "SaveGameWidget.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Dialogues/CreateSaveDialogue.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "TellMeYourSecret/GameInstances/SaveManager.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/UMG/Colors.h"

void USaveGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SaveManager = GetGameInstance()->GetSubsystem<USaveManager>();

	SaveButton->OnClicked.AddDynamic(this, &USaveGameWidget::SaveButtonClicked);
	DeleteButton->OnClicked.AddDynamic(this, &USaveGameWidget::DeleteButtonClicked);
	LoadButton->OnClicked.AddDynamic(this, &USaveGameWidget::LoadButtonClicked);
	StartGameButton->OnClicked.AddDynamic(this, &USaveGameWidget::StartGameButtonClicked);
}

void USaveGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!SaveGameInfo.NativeSlotName.IsEmpty())
	{
		LayoutSwitcher->SetActiveWidgetIndex(1);
	}
	else
	{
		LoadButton->SetVisibility(ESlateVisibility::Hidden);
		DeleteButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USaveGameWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	Border->SetColor(EPalette::Pink);
	HoverBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	if (UGameplayStatics::IsGamePaused(this))
	{
		SaveButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SaveButton->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USaveGameWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	Border->SetColor(EPalette::White);
	HoverBox->SetVisibility(ESlateVisibility::Hidden);
}

FText USaveGameWidget::GetSaveDateText() const
{
	FFormatNamedArguments Args;
	Args.Add("Date", UKismetTextLibrary::AsDate_DateTime(SaveGameInfo.Date));
	return FText::Format(NSLOCTEXT("SaveGame", "SaveDate", "{Date}"), Args);
}

void USaveGameWidget::SaveButtonClicked()
{
	if (SaveGameInfo.NativeSlotName.IsEmpty())
	{
		UCreateSaveDialogue* Confirm = CreateWidget<UCreateSaveDialogue>(GetOwningPlayer(), ConfirmCreateWidgetClass);

		Confirm->AddToViewport();
		Confirm->OnSaveResponse.AddDynamic(this, &USaveGameWidget::ConfirmCreate);
	}
	else
	{
		UConfirmDialogue* Confirm = CreateWidget<UConfirmDialogue>(GetOwningPlayer(), ConfirmSaveWidgetClass);
		Confirm->Title = NSLOCTEXT("Save", "SaveGame.Save.Title", "Overwrite this slot");
		Confirm->Message = NSLOCTEXT("Save", "SaveGame.Save.Message", "All previous progress will be overridden");

		Confirm->AddToViewport();
		Confirm->OnResponse.AddDynamic(this, &USaveGameWidget::ConfirmSave);
	}
}

void USaveGameWidget::DeleteButtonClicked()
{
	if (!SaveGameInfo.NativeSlotName.IsEmpty())
	{
		UConfirmDialogue* Confirm = CreateWidget<UConfirmDialogue>(GetOwningPlayer(), ConfirmDeleteWidgetClass);
		Confirm->Title = NSLOCTEXT("Save", "SaveGame.Delete.Title", "Do you want to delete this slot?");
		Confirm->Message = NSLOCTEXT("Save", "SaveGame.Delete.Message", "This cannot be undone");

		Confirm->AddToViewport();
		Confirm->OnResponse.AddDynamic(this, &USaveGameWidget::ConfirmDelete);
	}
}

void USaveGameWidget::LoadButtonClicked()
{
	if (!SaveGameInfo.NativeSlotName.IsEmpty())
	{
		UConfirmDialogue* Confirm = CreateWidget<UConfirmDialogue>(GetOwningPlayer(), ConfirmLoadWidgetClass);
		Confirm->Title = NSLOCTEXT("Save", "SaveGame.Load.Title", "Load this slot");
		Confirm->Message = NSLOCTEXT("Save", "SaveGame.Load.Message", "All unsaved progress will be lost");

		Confirm->AddToViewport();
		Confirm->OnResponse.AddDynamic(this, &USaveGameWidget::ConfirmLoad);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USaveGameWidget::StartGameButtonClicked()
{
	if (!UGameplayStatics::IsGamePaused(this))
	{
		ConfirmLoad(true);
		return;
	}

	UConfirmDialogue* Confirm = CreateWidget<UConfirmDialogue>(GetOwningPlayer(), ConfirmSaveWidgetClass);
	Confirm->Title = NSLOCTEXT("Save", "SaveGame.New.Title", "Create new Game");
	Confirm->Message = NSLOCTEXT("Save", "SaveGame.Load.Message", "All unsaved progress will be lost");

	Confirm->AddToViewport();
	Confirm->OnResponse.AddDynamic(this, &USaveGameWidget::ConfirmLoad);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USaveGameWidget::ConfirmCreate(const bool bCreate, FString Name)
{
	if (!bCreate)
	{
		return;
	}
	SaveGameInfo.SlotName = Name;
	ConfirmSave(true);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USaveGameWidget::ConfirmSave(const bool bSave)
{
	if (bSave)
	{
		SaveManager->SaveGame(SaveGameInfo);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USaveGameWidget::ConfirmDelete(const bool bDelete)
{
	if (bDelete)
	{
		SaveManager->DeleteGame(SaveGameInfo);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void USaveGameWidget::ConfirmLoad(const bool bLoad)
{
	if (bLoad)
	{
		SaveManager->LoadGame(SaveGameInfo.NativeSlotName);
	}
}
