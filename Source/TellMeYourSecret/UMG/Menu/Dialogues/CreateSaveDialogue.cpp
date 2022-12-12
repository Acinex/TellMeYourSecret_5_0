// Copyright Acinex Games 2020

#include "CreateSaveDialogue.h"

void UCreateSaveDialogue::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	FGetBool Delegate;

	Delegate.BindDynamic(this, &UCreateSaveDialogue::SaveEnabled);
	ConfirmButton->bIsEnabledDelegate = Delegate;
	SaveSlotNameTextBox->OnTextCommitted.AddDynamic(this, &UCreateSaveDialogue::SaveSlotNameCommit);
}

void UCreateSaveDialogue::Cancel()
{
	OnSaveResponse.Broadcast(false, TEXT(""));
	Super::Cancel();
}

void UCreateSaveDialogue::Confirm()
{
	OnSaveResponse.Broadcast(true, SaveSlotNameTextBox->GetText().ToString());
	Super::Confirm();
}

// ReSharper disable once CppMemberFunctionMayBeConst
bool UCreateSaveDialogue::SaveEnabled()
{
	return !SaveSlotNameTextBox->GetText().IsEmpty();
}

void UCreateSaveDialogue::SaveSlotNameCommit(const FText& Text, const ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		Confirm();
	}
}
