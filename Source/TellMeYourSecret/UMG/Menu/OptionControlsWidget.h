// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

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
	UUserWidget* OptionsButtonGroup;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Options)
	UWidgetSwitcher* OptionSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Audio)
	USlider* MasterVolumeSlider;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Audio)
	USlider* VoiceVolumeSlider;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Audio)
	USlider* EnvironmentVolumeSlider;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Audio)
	USlider* EffectVolumeSlider;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Audio)
	USlider* MusicVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UComboBoxString* ResolutionComboBox;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UUserWidget* ViewDistanceTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UUserWidget* ShadowTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UUserWidget* AntiAliasingTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UUserWidget* TextureTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UUserWidget* VisualEffectTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UUserWidget* PostProcessingTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UUserWidget* FoliageTabBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Video)
	UUserWidget* ShadingTabBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=General)
	UComboBoxString* LanguageComboBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Controls)
	UListView* KeyBindingsList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category=Controls)
	UButton* ApplyButton;

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
	
	void UpdateVolumes() const;

	UFUNCTION()
	void ChangeLanguage(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void ChangeResolution(FString SelectedItem, ESelectInfo::Type SelectionType);

	void CreateKeySelector() const;

	UFUNCTION()
	void ApplySettings();
};
