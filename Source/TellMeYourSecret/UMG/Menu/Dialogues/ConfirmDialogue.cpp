// Copyright Acinex Games 2020

#include "ConfirmDialogue.h"

void UConfirmDialogue::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UCommonButtonBase::FCommonButtonEvent CommonButtonEvent = CancelButton->OnClicked();
	CommonButtonEvent.AddUFunction(this, "Cancel");
	CommonButtonEvent = ConfirmButton->OnClicked();
	CommonButtonEvent.AddUFunction(this, "Confirm");
}

void UConfirmDialogue::Cancel()
{
	RemoveFromParent();
	OnResponse.Broadcast(false);
}

void UConfirmDialogue::Confirm()
{
	RemoveFromParent();
	OnResponse.Broadcast(true);
}
