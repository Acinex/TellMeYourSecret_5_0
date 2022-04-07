// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/WSModernButton.h"
#include "Widgets/WSModernTabBar.h"
#include "Widgets/WSModernSlider.h"

#include "OptionControlsWidget.generated.h"

class UOptionSwitch;
class UButtonGroupWidget;
class UCheckBox;
class UListView;
class UInputSettings;
class UInputKeySelector;
class UComboBoxString;
class UButton;
class UTellMeYourSecretGameInstance;
class UWidgetSwitcher;
class USlider;
class UWidgetStudioModernComboBox;
class UWidgetStudioButtonGroup;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TELLMEYOURSECRET_API UOptionControlsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	explicit UOptionControlsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Options)
	UWidgetStudioButtonGroup* OptionsButtonGroup;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Options)
	UWidgetSwitcher* OptionSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Audio)
	UWidgetStudioModernSlider* MasterVolumeSlider;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Audio)
	UWidgetStudioModernSlider* VoiceVolumeSlider;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Audio)
	UWidgetStudioModernSlider* EnvironmentVolumeSlider;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Audio)
	UWidgetStudioModernSlider* EffectVolumeSlider;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Audio)
	UWidgetStudioModernSlider* MusicVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UWidgetStudioModernComboBox* ResolutionComboBox;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UWidgetStudioModernTabBar* ViewDistanceTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UWidgetStudioModernTabBar* ShadowTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UWidgetStudioModernTabBar* AntiAliasingTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UWidgetStudioModernTabBar* TextureTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UWidgetStudioModernTabBar* VisualEffectTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UWidgetStudioModernTabBar* PostProcessingTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UWidgetStudioModernTabBar* FoliageTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UWidgetStudioModernTabBar* ShadingTabBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=General)
	UWidgetStudioModernComboBox* LanguageComboBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Controls)
	UListView* KeyBindingsList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Controls)
	UWidgetStudioModernButton* ApplyButton;

	UPROPERTY(BlueprintReadOnly)
	UTellMeYourSecretGameInstance* GameInstance;

private:
	UPROPERTY()
	UInputSettings* InputSettings;

	UFUNCTION()
	void ShowOptionsTab(int32 Index);

	UFUNCTION()
	void MasterVolumeChanged(float Value);
	UFUNCTION()
	void VoiceVolumeChanged(float Value);
	UFUNCTION()
	void EnvironmentVolumeChanged(float Value);
	UFUNCTION()
	void EffectVolumeChanged(float Value);
	UFUNCTION()
	void MusicVolumeChanged(float Value);

	void InitializeGraphicOptions(UWidgetStudioModernTabBar* TabBar) const;

	UFUNCTION()
	void UpdateViewDistance(int32 CurrentIndex, FButtonOptions Option);
	UFUNCTION()
	void UpdateShadowQuality(int32 CurrentIndex, FButtonOptions Option);
	UFUNCTION()
	void UpdateAntiAliasingQuality(int32 CurrentIndex, FButtonOptions Option);
	UFUNCTION()
	void UpdateTextureQuality(int32 CurrentIndex, FButtonOptions Option);
	UFUNCTION()
	void UpdateVisualEffectQuality(int32 CurrentIndex, FButtonOptions Option);
	UFUNCTION()
	void UpdatePostProcessingQuality(int32 CurrentIndex, FButtonOptions Option);
	UFUNCTION()
	void UpdateFoliageQuality(int32 CurrentIndex, FButtonOptions Option);
	UFUNCTION()
	void UpdateShadingQuality(int32 CurrentIndex, FButtonOptions Option);

	void UpdateVolumes() const;

	UFUNCTION()
	void ChangeLanguage(int32 CurrentIndex, FButtonOptions Option);
	UFUNCTION()
	void ChangeResolution(int32 CurrentIndex, FButtonOptions Option);

	void CreateKeySelector() const;

	UFUNCTION()
	void ApplySettings(UWidgetStudioButtonBase* CallingButton);
};
