// Copyright Acinex Games 2020

#include "ButtonGroupWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UButtonGroupWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	Clear();

	for (UCheckBox* CheckBox : CheckBoxes)
	{
		CheckBox->OnCheckStateChanged.Clear();
	}

	CheckBoxes.Empty();

	for (const FText Option : Options)
	{
		UTextBlock* TextBlock = WidgetTree->ConstructWidget<UTextBlock>();
		TextBlock->SetText(Option);
		TextBlock->SetJustification(ETextJustify::Center);

		UCheckBox* CheckBox = WidgetTree->ConstructWidget<UCheckBox>();
		CheckBox->WidgetStyle.SetCheckBoxType(ESlateCheckBoxType::ToggleButton);
		CheckBox->AddChild(TextBlock);

		UClickProxy* Proxy = NewObject<UClickProxy>(this);
		Proxy->Option      = Option;
		Proxy->Group       = this;
		CheckBox->OnCheckStateChanged.AddDynamic(Proxy, &UClickProxy::Broadcast);

		CheckBoxes.Add(CheckBox);

		AddButton(CheckBox);
	}
}

void UButtonGroupWidget::Select(const FText Option)
{
	for (int8 I = 0; I < CheckBoxes.Num(); I++)
	{
		const bool bIsChecked = Option.EqualTo(Options[I]);
		CheckBoxes[I]->SetIsChecked(bIsChecked);

		if (bIsChecked)
		{
			OnOptionClicked.Broadcast(I);
		}
	}
}

void UButtonGroupWidget::SetSelected(const int8 Index)
{
	for (int8 I = 0; I < CheckBoxes.Num(); I++)
	{
		CheckBoxes[I]->SetIsChecked(I == Index);
	}
}
