// Copyright Acinex Games 2020

#include "ConfirmDialogue.h"


void UConfirmDialogue::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CancelButton->OnReleased.AddDynamic(this, &UConfirmDialogue::Cancel);
	ConfirmButton->OnReleased.AddDynamic(this, &UConfirmDialogue::Confirm);
}

void UConfirmDialogue::Cancel()
{
	RemoveFromViewport();
	OnResponse.Broadcast(false);
}

void UConfirmDialogue::Confirm()
{
	RemoveFromViewport();
	OnResponse.Broadcast(true);
}
