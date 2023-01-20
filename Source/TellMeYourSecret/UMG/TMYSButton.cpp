// Copyright Acinex Games 2020


#include "TMYSButton.h"

void UTMYSButton::SetText(const FText InText)
{
	TextBlock->SetText(InText);
}

void UTMYSButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (TextBlock != nullptr)
		TextBlock->SetText(Text);
}
