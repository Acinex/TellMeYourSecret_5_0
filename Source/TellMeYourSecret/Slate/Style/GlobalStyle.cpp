#include "GlobalStyle.h"

void FGlobalStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	ButtonStyle.GetResources(OutBrushes);
	Slider.GetResources(OutBrushes);
	TextStyle.GetResources(OutBrushes);
}

const FName FGlobalStyle::TypeName = TEXT("FGlobalStyle");

const FName FGlobalStyle::GetTypeName() const
{
	return TypeName;
}

const FGlobalStyle& FGlobalStyle::GetDefault()
{
	static FGlobalStyle Default;
	return Default;
}

UGlobalMenuStyle::UGlobalMenuStyle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}