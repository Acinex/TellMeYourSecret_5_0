#pragma once

#include "SlateBasics.h"
#include "GlobalStyle.generated.h" 

// Provides a group of global style settings for our game menus! 
USTRUCT()
struct FGlobalStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()
		// Stores a list of Brushes we are using (we aren't using any) into OutBrushes.
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;

	// Stores the TypeName for our widget style.
	static const FName TypeName;

	// Retrieves the type name for our global style, which will be used by our Style Set to load the right file. 
	virtual const FName GetTypeName() const override;
        
	// Allows us to set default values for our various styles. 
	static const FGlobalStyle& GetDefault(); 

	UPROPERTY(EditAnywhere, Category = Appearance)
	FButtonStyle ButtonStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
	FSliderStyle Slider;

	UPROPERTY(EditAnywhere, Category = Appearance)
	FTextBlockStyle TextStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
	FComboBoxStyle ComboBox;
};

// Provides a widget style container to allow us to edit properties in-editor
UCLASS(hidecategories = Object, MinimalAPI)
class UGlobalMenuStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:
	// This is our actual Style object. 
	UPROPERTY(EditAnywhere, Category = Appearance, meta = (ShowOnlyInnerProperties))
	FGlobalStyle MenuStyle;

	// Retrievs the style that this container manages. 
	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&MenuStyle);
	}

};