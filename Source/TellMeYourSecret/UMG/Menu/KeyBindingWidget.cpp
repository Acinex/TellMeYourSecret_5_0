// Copyright Acinex Games 2020

#include "KeyBindingWidget.h"

#include "Components/InputKeySelector.h"
#include "Components/TextBlock.h"

const static FText ActionText    = NSLOCTEXT("Options", "Options.Controls.ActionText", "Press a key...");
const static FText NoBindingText = NSLOCTEXT("Options", "Options.Controls.NoBinding", "No Binding");

void UKeyBindingWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	KeyBinding = Cast<UKeyBinding>(ListItemObject);
	Label->SetText(KeyBinding->Label);

	const FInputChord Chord(KeyBinding->KeyMapping.Key, KeyBinding->KeyMapping.bShift, KeyBinding->KeyMapping.bCtrl, KeyBinding->KeyMapping.bAlt, KeyBinding->KeyMapping.bCmd);
	KeySelector->SetSelectedKey(Chord);
}

void UKeyBindingWidget::NativeOnInitialized()
{
	KeySelector->KeySelectionText   = ActionText;
	KeySelector->NoKeySpecifiedText = NoBindingText;
}
