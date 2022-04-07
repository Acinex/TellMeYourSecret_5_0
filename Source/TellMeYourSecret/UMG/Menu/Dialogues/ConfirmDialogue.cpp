// Copyright Acinex Games 2020

#include "ConfirmDialogue.h"

#include "Widgets/WSModernButton.h"

void UConfirmDialogue::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CancelButton->OnReleased.AddDynamic(this, &UConfirmDialogue::Cancel);
	ConfirmButton->OnReleased.AddDynamic(this, &UConfirmDialogue::Confirm);
}

void UConfirmDialogue::Cancel(UWidgetStudioButtonBase* CallingButton)
{
	RemoveFromViewport();
	OnResponse.Broadcast(false);
}

void UConfirmDialogue::Confirm(UWidgetStudioButtonBase* CallingButton)
{
	RemoveFromViewport();
	OnResponse.Broadcast(true);
}
