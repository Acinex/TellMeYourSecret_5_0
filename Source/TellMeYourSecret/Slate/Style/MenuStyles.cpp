#include "MenuStyles.h"

#include "Slate/SlateGameResources.h"
#include "Styling/SlateStyleRegistry.h"
#include "TellMeYourSecret/UMG/Colors.h"

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(StyleRef->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<FSlateStyleSet> FMenuStyles::MenuStyleInstance = nullptr;

void FMenuStyles::Initialize()
{
	if (!MenuStyleInstance.IsValid())
	{
		MenuStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*MenuStyleInstance);
	}
}

void FMenuStyles::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*MenuStyleInstance);
	ensure(MenuStyleInstance.IsUnique());
	MenuStyleInstance.Reset();
}

FName FMenuStyles::GetStyleSetName()
{
	static FName StyleSetName(TEXT("MenuStyles"));
	return StyleSetName;
}

TSharedRef<FSlateStyleSet> FMenuStyles::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(GetStyleSetName(), "/Game/UI/Styles", "/Game/UI/Styles");

	// const FSliderStyle SliderStyle = FSliderStyle()
	//                                 .SetNormalBarImage(FSlateColorBrush(Colors::Pink))
	//                                 .SetHoveredBarImage(FSlateColorBrush(FColor::White))
	//                                 .SetDisabledBarImage(FSlateColorBrush(FLinearColor::Gray))
	//                                 .SetNormalThumbImage( IMAGE_BRUSH( "slider-thumb", FVector2D(20, 20) ) )
	//                                 .SetHoveredThumbImage(IMAGE_BRUSH("slider-thumb", FVector2D(20, 20)))
	//                                 .SetDisabledThumbImage( IMAGE_BRUSH( "slider-thumb", FVector2D(20, 20) ) )
	//                                 .SetBarThickness(6.0f);
	// StyleRef->Set( "Slider", SliderStyle );
	return StyleRef;
}

const ISlateStyle& FMenuStyles::Get()
{
	if (!MenuStyleInstance.IsValid())
	{
		Initialize();
	}

	return *MenuStyleInstance;
}
