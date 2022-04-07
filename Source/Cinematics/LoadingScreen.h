#pragma once


#include "CinematicsSettings.h"
#include "Engine.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "Widgets/Images/SThrobber.h"

struct FLoadingScreenBrush : FSlateDynamicImageBrush, FGCObject
{
	FLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(nullptr, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override
	{
		FSlateBrush::AddReferencedObjects(Collector);
	}
};

class SLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLoadingScreen)
	{
	}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{

		TArray<FName> Textures= UCinematicsSettings::Get()->Textures;

		const int32 Index = FMath::RandRange(0, Textures.Num() - 1);

		LoadingScreenBrush = MakeShareable(new FLoadingScreenBrush(Textures[Index], FVector2D(1920, 1080)));

		ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			 .HAlign(HAlign_Fill)
			 .VAlign(VAlign_Fill)
			[
				SNew(SImage)
			   .Image(LoadingScreenBrush.Get())
			]
			+ SOverlay::Slot()
			 .HAlign(HAlign_Fill)
			 .VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				 .VAlign(VAlign_Bottom)
				 .HAlign(HAlign_Right)
				 .Padding(FMargin(10.0f))
				[
					SNew(SThrobber)
				   .Visibility(this, &SLoadingScreen::GetLoadIndicatorVisibility)
				]
			]
		];
	}

private:
	EVisibility GetLoadIndicatorVisibility() const
	{
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}

	/** loading screen image brush */
	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};
