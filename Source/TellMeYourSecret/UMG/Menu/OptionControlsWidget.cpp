// Copyright Acinex Games 2020

#include "OptionControlsWidget.h"

#include "KeyBindingWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "GameFramework/GameUserSettings.h"
#include "GameFramework/InputSettings.h"
#include "Internationalization/Culture.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"
#include "TellMeYourSecret/Model/Save/Settings.h"

const static TMap<FName, FText> InputNames = {
	{FName(TEXT("Crouch")), NSLOCTEXT("Options", "Options.KeyBindings.Key.Crouch", "Crouch")},
	{FName(TEXT("Interact")), NSLOCTEXT("Options", "Options.KeyBindings.Key.Interact", "Interact")},
	{FName(TEXT("Jump")), NSLOCTEXT("Options", "Options.KeyBindings.Key.Jump", "Jump")},
	{
		FName(TEXT("ToggleSmartphone")),
		NSLOCTEXT("Options", "Options.KeyBindings.Key.ToggleSmartphone", "Toggle Smartphone")
	},
	{FName(TEXT("Sprint")), NSLOCTEXT("Options", "Options.KeyBindings.Key.Sprint", "Sprint")},
	{FName(TEXT("ToggleCamera")), NSLOCTEXT("Options", "Options.KeyBindings.Key.ToggleCamera", "Toggle camera")}
};

UOptionControlsWidget::UOptionControlsWidget(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	InputSettings = UInputSettings::GetInputSettings();
}

void UOptionControlsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());
	UpdateVolumes();

	// OptionsButtonGroup->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::ShowOptionsTab);

	//MasterVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionControlsWidget::MasterVolumeChanged);
	//VoiceVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionControlsWidget::VoiceVolumeChanged);
	//EnvironmentVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionControlsWidget::EnvironmentVolumeChanged);
	//EffectVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionControlsWidget::EffectVolumeChanged);
	//MusicVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionControlsWidget::MusicVolumeChanged);

	LanguageComboBox->ClearOptions();
	for (FString CultureName : GameInstance->GetCultureNames())
	{
		LanguageComboBox->AddOption(CultureName);
	}

	LanguageComboBox->SetSelectedIndex(GameInstance->GetCultureNames().Find(FInternationalization::Get().GetCurrentLanguage()->GetDisplayName()));

	LanguageComboBox->OnSelectionChanged.AddDynamic(this, &UOptionControlsWidget::ChangeLanguage);

	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);


	for (const FIntPoint Point : Resolutions)
	{
		ResolutionComboBox->AddOption(FString::FromInt(Point.X) + TEXT("x") + FString::FromInt(Point.Y));
	}

	const FIntPoint Resolution = UGameUserSettings::GetGameUserSettings()->GetScreenResolution();
	ResolutionComboBox->SetSelectedOption(FString::FromInt(Resolution.X) + TEXT("x") + FString::FromInt(Resolution.Y));
	ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UOptionControlsWidget::ChangeResolution);

	// ViewDistanceTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateViewDistance);
	// ShadowTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateShadowQuality);
	// AntiAliasingTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateAntiAliasingQuality);
	// TextureTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateTextureQuality);
	// VisualEffectTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateVisualEffectQuality);
	// PostProcessingTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdatePostProcessingQuality);
	// FoliageTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateFoliageQuality);
	// ShadingTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateShadingQuality);
	//
	// ApplyButton->OnClicked.AddDynamic(this, &UOptionControlsWidget::ApplySettings);
}

void UOptionControlsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateVolumes();
	CreateKeySelector();

	// ViewDistanceTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetViewDistanceQuality());
	// ShadowTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetShadowQuality());
	// AntiAliasingTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetAntiAliasingQuality());
	// TextureTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetTextureQuality());
	// VisualEffectTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetVisualEffectQuality());
	// PostProcessingTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetPostProcessingQuality());
	// FoliageTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetFoliageQuality());
	// ShadingTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetShadingQuality());
}

void UOptionControlsWidget::ShowOptionsTab(const int32 Index)
{
	OptionSwitcher->SetActiveWidgetIndex(Index);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UOptionControlsWidget::MasterVolumeChanged(const float Value)
{
	GameInstance->UpdateVolume(EVolumeType::Master, Value / 100);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UOptionControlsWidget::VoiceVolumeChanged(const float Value)
{
	GameInstance->UpdateVolume(EVolumeType::Voice, Value / 100);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UOptionControlsWidget::EnvironmentVolumeChanged(const float Value)
{
	GameInstance->UpdateVolume(EVolumeType::Environment, Value / 100);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UOptionControlsWidget::EffectVolumeChanged(const float Value)
{
	GameInstance->UpdateVolume(EVolumeType::Effects, Value / 100);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UOptionControlsWidget::MusicVolumeChanged(const float Value)
{
	UE_LOG(LogTellMeYourSecret, Log, TEXT("Update Music to %f"), Value)
	GameInstance->UpdateVolume(EVolumeType::Music, Value / 100);
}

void UOptionControlsWidget::UpdateVolumes() const
{
	// MasterVolumeSlider->SetValue(GameInstance->GetVolume(EVolumeType::Master) * 100);
	// VoiceVolumeSlider->SetValue(GameInstance->GetVolume(EVolumeType::Voice) * 100);
	// EnvironmentVolumeSlider->SetValue(GameInstance->GetVolume(EVolumeType::Environment) * 100);
	// EffectVolumeSlider->SetValue(GameInstance->GetVolume(EVolumeType::Effects) * 100);
	// MusicVolumeSlider->SetValue(GameInstance->GetVolume(EVolumeType::Music) * 100);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UOptionControlsWidget::ChangeLanguage(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	GameInstance->SetLanguage(SelectedItem);
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppMemberFunctionMayBeStatic
void UOptionControlsWidget::ChangeResolution(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	FString XString;
	FString YString;
	SelectedItem.Split("x", &XString, &YString);

	UGameUserSettings::GetGameUserSettings()->SetScreenResolution({
		UKismetStringLibrary::Conv_StringToInt(XString), UKismetStringLibrary::Conv_StringToInt(YString)
	});
}

void UOptionControlsWidget::CreateKeySelector() const
{
	TArray<UKeyBinding*> KeyBindings;

	for (const TTuple<FName, FText> Part : InputNames)
	{
		TArray<FInputActionKeyMapping> ActionKeyMappings;
		InputSettings->GetActionMappingByName(Part.Key, ActionKeyMappings);
		if (ActionKeyMappings.Num())
		{
			UKeyBinding* KeyBinding = NewObject<UKeyBinding>();
			KeyBinding->KeyMapping = ActionKeyMappings[0];
			KeyBinding->Label = Part.Value;

			KeyBindings.Add(KeyBinding);
		}
	}
	KeyBindingsList->SetListItems(KeyBindings);
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppMemberFunctionMayBeStatic
void UOptionControlsWidget::ApplySettings()
{
	UGameUserSettings::GetGameUserSettings()->ApplySettings(false);
}
