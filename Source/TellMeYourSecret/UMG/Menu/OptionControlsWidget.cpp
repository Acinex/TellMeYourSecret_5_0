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
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"
#include "TellMeYourSecret/Model/Save/Settings.h"
#include "Widgets/WSModernComboBox.h"

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

	OptionsButtonGroup->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::ShowOptionsTab);

	MasterVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionControlsWidget::MasterVolumeChanged);
	VoiceVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionControlsWidget::VoiceVolumeChanged);
	EnvironmentVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionControlsWidget::EnvironmentVolumeChanged);
	EffectVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionControlsWidget::EffectVolumeChanged);
	MusicVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionControlsWidget::MusicVolumeChanged);

	LanguageComboBox->ClearOptions();
	for (FString CultureName : GameInstance->GetCultureNames())
	{
		FButtonOptions Option;
		Option.Text = FText::FromString(CultureName);
		LanguageComboBox->AddOption(Option);
	}

	LanguageComboBox->SetCurrentIndex(GameInstance->GetCultureNames().Find(FInternationalization::Get().GetCurrentLanguage()->GetDisplayName()));

	LanguageComboBox->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::ChangeLanguage);

	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);


	for (const FIntPoint Point : Resolutions)
	{
		FButtonOptions Option;
		Option.Text = FText::FromString(FString::FromInt(Point.X) + TEXT("x") + FString::FromInt(Point.Y));
		Option.CheckedContentColor = EPalette::SecondaryBackground;
		ResolutionComboBox->AddOption(Option);
	}

	const FIntPoint Resolution = UGameUserSettings::GetGameUserSettings()->GetScreenResolution();
	ResolutionComboBox->SetCurrentIndexViaOptionText(FText::FromString(FString::FromInt(Resolution.X) + TEXT("x") + FString::FromInt(Resolution.Y)));
	ResolutionComboBox->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::ChangeResolution);

	InitializeGraphicOptions(ViewDistanceTabBar);
	InitializeGraphicOptions(ShadowTabBar);
	InitializeGraphicOptions(AntiAliasingTabBar);
	InitializeGraphicOptions(TextureTabBar);
	InitializeGraphicOptions(VisualEffectTabBar);
	InitializeGraphicOptions(PostProcessingTabBar);
	InitializeGraphicOptions(FoliageTabBar);
	InitializeGraphicOptions(ShadingTabBar);

	ViewDistanceTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateViewDistance);
	ShadowTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateShadowQuality);
	AntiAliasingTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateAntiAliasingQuality);
	TextureTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateTextureQuality);
	VisualEffectTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateVisualEffectQuality);
	PostProcessingTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdatePostProcessingQuality);
	FoliageTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateFoliageQuality);
	ShadingTabBar->OnCurrentIndexChanged.AddDynamic(this, &UOptionControlsWidget::UpdateShadingQuality);

	ApplyButton->OnReleased.AddDynamic(this, &UOptionControlsWidget::ApplySettings);
}

void UOptionControlsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateVolumes();
	CreateKeySelector();

	ViewDistanceTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetViewDistanceQuality());
	ShadowTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetShadowQuality());
	AntiAliasingTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetAntiAliasingQuality());
	TextureTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetTextureQuality());
	VisualEffectTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetVisualEffectQuality());
	PostProcessingTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetPostProcessingQuality());
	FoliageTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetFoliageQuality());
	ShadingTabBar->SetCurrentIndex(UGameUserSettings::GetGameUserSettings()->GetShadingQuality());
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
	GameInstance->UpdateVolume(EVolumeType::Music, Value / 100);
}

void UOptionControlsWidget::InitializeGraphicOptions(UWidgetStudioModernTabBar* TabBar) const
{
	FButtonOptions Low;
	Low.Text = FText::FromString(TEXT("Low"));

	FButtonOptions Medium;
	Medium.Text = FText::FromString(TEXT("Medium"));

	FButtonOptions High;
	High.Text = FText::FromString(TEXT("High"));

	FButtonOptions Epic;
	Epic.Text = FText::FromString(TEXT("Epic"));

	FButtonOptions Cinematic;
	Cinematic.Text = FText::FromString(TEXT("Cinematic"));

	TabBar->AddOption(Low);
	TabBar->AddOption(Medium);
	TabBar->AddOption(High);
	TabBar->AddOption(Epic);
	TabBar->AddOption(Cinematic);
}

void UOptionControlsWidget::UpdateViewDistance(const int32 CurrentIndex, FButtonOptions Option)
{
	UGameUserSettings::GetGameUserSettings()->SetViewDistanceQuality(CurrentIndex);
}

void UOptionControlsWidget::UpdateShadowQuality(const int32 CurrentIndex, FButtonOptions Option)
{
	UGameUserSettings::GetGameUserSettings()->SetShadowQuality(CurrentIndex);
}

void UOptionControlsWidget::UpdateAntiAliasingQuality(const int32 CurrentIndex, FButtonOptions Option)
{
	UGameUserSettings::GetGameUserSettings()->SetAntiAliasingQuality(CurrentIndex);
}

void UOptionControlsWidget::UpdateTextureQuality(const int32 CurrentIndex, FButtonOptions Option)
{
	UGameUserSettings::GetGameUserSettings()->SetTextureQuality(CurrentIndex);
}

void UOptionControlsWidget::UpdateVisualEffectQuality(const int32 CurrentIndex, FButtonOptions Option)
{
	UGameUserSettings::GetGameUserSettings()->SetVisualEffectQuality(CurrentIndex);
}

void UOptionControlsWidget::UpdatePostProcessingQuality(const int32 CurrentIndex, FButtonOptions Option)
{
	UGameUserSettings::GetGameUserSettings()->SetPostProcessingQuality(CurrentIndex);
}

void UOptionControlsWidget::UpdateFoliageQuality(const int32 CurrentIndex, FButtonOptions Option)
{
	UGameUserSettings::GetGameUserSettings()->SetFoliageQuality(CurrentIndex);
}

void UOptionControlsWidget::UpdateShadingQuality(const int32 CurrentIndex, FButtonOptions Option)
{
	UGameUserSettings::GetGameUserSettings()->SetShadingQuality(CurrentIndex);
}

void UOptionControlsWidget::UpdateVolumes() const
{
	MasterVolumeSlider->SetValue(GameInstance->GetVolume(EVolumeType::Master) * 100);
	VoiceVolumeSlider->SetValue(GameInstance->GetVolume(EVolumeType::Voice) * 100);
	EnvironmentVolumeSlider->SetValue(GameInstance->GetVolume(EVolumeType::Environment) * 100);
	EffectVolumeSlider->SetValue(GameInstance->GetVolume(EVolumeType::Effects) * 100);
	MusicVolumeSlider->SetValue(GameInstance->GetVolume(EVolumeType::Music) * 100);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UOptionControlsWidget::ChangeLanguage(const int32 CurrentIndex, const FButtonOptions Option)
{
	GameInstance->SetLanguage(Option.Text.ToString());
}

// ReSharper disable once CppMemberFunctionMayBeConst
// ReSharper disable once CppMemberFunctionMayBeStatic
void UOptionControlsWidget::ChangeResolution(int32 CurrentIndex, const FButtonOptions Option)
{
	FString XString;
	FString YString;
	Option.Text.ToString().Split("x", &XString, &YString);

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
void UOptionControlsWidget::ApplySettings(UWidgetStudioButtonBase* CallingButton)
{
	UGameUserSettings::GetGameUserSettings()->ApplySettings(false);
}
