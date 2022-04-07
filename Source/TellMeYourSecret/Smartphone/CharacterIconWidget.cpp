#include "CharacterIconWidget.h"

#include "TellMeYourSecret/Characters/CharacterData.h"
#include "Components/Image.h"
#include "TellMeYourSecret/UMG/Colors.h"

void UCharacterIconWidget::SetCharacterData(UCharacterData* InCharacterData)
{
	CharacterData = InCharacterData;
}

void UCharacterIconWidget::SetSelected(const bool bSelected)
{
	ColorAndOpacity = bSelected ? Colors::MarinaBlue : Colors::Transparent;
}

void UCharacterIconWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	SetCharacterData(Cast<UCharacterData>(ListItemObject));
}

void UCharacterIconWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BrushImage->BrushDelegate.BindDynamic(this, &UCharacterIconWidget::GetBrush);
	ContactImage->BrushDelegate.BindDynamic(this, &UCharacterIconWidget::GetImage);
}

// ReSharper disable once CppMemberFunctionMayBeConst
FSlateBrush UCharacterIconWidget::GetBrush()
{
	FSlateBrush Brush;

	Brush.TintColor = FSlateColor(Color);
	return Brush;
}

// ReSharper disable once CppMemberFunctionMayBeConst
FSlateBrush UCharacterIconWidget::GetImage()
{
	FSlateBrush Brush;
	if (CharacterData)
	{
		Brush.SetResourceObject(CharacterData->Image);
	}

	return Brush;
}
