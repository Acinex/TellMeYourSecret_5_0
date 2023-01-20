// Copyright Acinex Games 2020

#include "ConfirmDialogue.h"

#include "TellMeYourSecret/UMG/Menu/UIBase.h"

void UConfirmDialogue::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UCommonButtonBase::FCommonButtonEvent CommonButtonEvent = CancelButton->OnClicked();
	CommonButtonEvent.AddUFunction(this, "Cancel");
	CommonButtonEvent = ConfirmButton->OnClicked();
	CommonButtonEvent.AddUFunction(this, "Confirm");
}

void UConfirmDialogue::NativeOnActivated()
{
	Super::NativeOnActivated();

	GetDesiredFocusTarget()->SetFocus();
}

UWidget* UConfirmDialogue::NativeGetDesiredFocusTarget() const
{
	return ConfirmButton;
}

void UConfirmDialogue::Setup(FText InTitle, FText InMessage, UUIBase* InOwner, int32 InIndex)
{
	Title = InTitle;
	Message = InMessage;
	Owner = InOwner;
	Index = InIndex;
}

void UConfirmDialogue::Cancel()
{
	DeactivateWidget();
	OnResponse.Broadcast(false);
}

void UConfirmDialogue::Confirm()
{
	DeactivateWidget();
	OnResponse.Broadcast(true);
}
