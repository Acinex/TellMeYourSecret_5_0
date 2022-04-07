/* 
* Copyright (c) 2021 THEIA INTERACTIVE.  All rights reserved.
*
* Website: https://widgetstudio.design
* Documentation: https://docs.widgetstudio.design
* Support: marketplace@theia.io
* Marketplace FAQ: https://marketplacehelp.epicgames.com
*/

#include "WidgetStudioEditor.h"
#include "WSSubsystem.h"
#include "WSSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "WSGlobals.h"
#include "PropertyEditorModule.h"
#include "Settings/ProjectPackagingSettings.h"

#include "DetailCustomization/WSBaseDetails.h"
#include "Widgets/WSModernButton.h"

#define LOCTEXT_NAMESPACE "FWidgetStudioEditor"
DEFINE_LOG_CATEGORY(LogWidgetStudio);

void FWidgetStudioEditor::StartupModule()
{
	RegisterDetailCustomization();

	// Register Settings
	RegisterSettings();
	WfSettings = GetMutableDefault<UWidgetStudioSettings>();

	WfSettings->Theme = DefaultTheme;
	WfSettings->IconSet = DefaultIconSet;
	WfSettings->Typography = DefaultTypography;

	//if there are values in ini file, override defaults
	WfSettings->LoadConfig();

	//initial loading of assets
	LoadObject<UWidgetStudioTheme>(nullptr, *WfSettings->Theme.ToString());
	LoadObject<UWidgetStudioIconSet>(nullptr, *WfSettings->IconSet.ToString());
	LoadObject<UWidgetStudioTypography>(nullptr, *WfSettings->Typography.ToString());

	//save values to ini file in case any of them are missing
	WfSettings->SaveConfig();
	
	VerifyWidgetStudioInCookDirs();
}

void FWidgetStudioEditor::ShutdownModule()
{
	if (UObjectInitialized())
	{
		UnregisterSettings();
	}

	UnregisterDetailCustomization();
}

bool FWidgetStudioEditor::SupportsDynamicReloading()
{
	return true;
}

void FWidgetStudioEditor::VerifyWidgetStudioInCookDirs() const
{
	if (!GConfig)
	{
		UE_LOG(LogWidgetStudio, Warning, TEXT("Could not get GConfig."));
		return;
	}

	const FString PackagingSettingsSection = TEXT("/Script/UnrealEd.ProjectPackagingSettings");
	const FString AddCookDirs = TEXT("+DirectoriesToAlwaysCook");
	const FString SubtractCookDirs = TEXT("-DirectoriesToAlwaysCook");
	const FString WidgetStudioShortPath = TEXT("(Path=\"/WidgetStudio\")");
	TArray<FString> SubtractCookDirsArray;
	TArray<FString> AddCookDirsArray;

	// if [/Script/UnrealEd.ProjectPackagingSettings] section doesn't exist in ini, create it and add /WidgetStudio to cook dirs
	if (!GConfig->DoesSectionExist(*PackagingSettingsSection, DefaultGameIni))
	{
		AddCookDirsArray.Add(WidgetStudioShortPath);
		GConfig->SetArray(*PackagingSettingsSection, *AddCookDirs, AddCookDirsArray, DefaultGameIni);
		return;
	}

	// delete any entries that remove /WidgetStudio from cook dirs
	GConfig->GetArray(*PackagingSettingsSection, *SubtractCookDirs, SubtractCookDirsArray, DefaultGameIni);
	if (SubtractCookDirsArray.Num() > 0)
	{
		TArray<int32> IndicesToRemove;

		for (int32 i = 0; i < SubtractCookDirsArray.Num(); i++)
		{
			if (SubtractCookDirsArray[i] == WidgetStudioShortPath)
			{
				IndicesToRemove.Add(i);
			}
		}

		// remove elements by moving backward through array so the relevant indices don't shift
		for (int32 i = IndicesToRemove.Num() - 1; i >= 0; i--)
		{
			SubtractCookDirsArray.RemoveAt(IndicesToRemove[i], 1, true);
		}

		GConfig->SetArray(*PackagingSettingsSection, *SubtractCookDirs, SubtractCookDirsArray, DefaultGameIni);
	}

	// add /WidgetStudio to cook dirs if not already present
	GConfig->GetArray(*PackagingSettingsSection, *AddCookDirs, AddCookDirsArray, DefaultGameIni);
	if (AddCookDirsArray.Num() > 0)
	{
		for (int32 i = 0; i < AddCookDirsArray.Num(); i++)
		{
			if (AddCookDirsArray[i] == WidgetStudioShortPath)
			{
				return;
			}
		}
	}
	
	AddCookDirsArray.Add(WidgetStudioShortPath);
	GConfig->SetArray(*PackagingSettingsSection, *AddCookDirs, AddCookDirsArray, DefaultGameIni);
}

bool FWidgetStudioEditor::HandleSettingsSaved() const
{
	UWidgetStudioSettings* Settings = GetMutableDefault<UWidgetStudioSettings>();
	constexpr bool ReSaveSettings = false; // FIXME: This bool is always false, thus Settings->SaveConfig() is never used.

	if (ReSaveSettings)
	{
		Settings->SaveConfig();
	}

	return true;
}

void FWidgetStudioEditor::RegisterSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create a new category
		const ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory(
			"Theia Interactive",
			LOCTEXT("RuntimeWDCategoryName", "Theia Interactive"),
			LOCTEXT("RuntimeWDCategoryDescription", "Game configuration settings for plugins created by Theia Interactive.")
			);

		// Register Settings
		const ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings(
			"Project",
			"Theia Interactive",
			"Widget Studio",
			LOCTEXT("RuntimeGeneralSettingsName", "Widget Studio"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Configure the properties of the Widget Studio."),
			GetMutableDefault<UWidgetStudioSettings>()
			);

		// Register the save handler
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FWidgetStudioEditor::HandleSettingsSaved);
		}
	}
}

void FWidgetStudioEditor::UnregisterSettings() const
{
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Theia Interactive", "General");
	}
}

void FWidgetStudioEditor::RegisterDetailCustomization() const
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout(
		UWidgetStudioBase::StaticClass()->GetFName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FModernButtonDetails::MakeInstance)
		);

	PropertyModule.NotifyCustomizationModuleChanged();

	UE_LOG(LogWidgetStudio, Verbose, TEXT("Detail Customizations Registered."))
}

void FWidgetStudioEditor::UnregisterDetailCustomization() const
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		
		PropertyModule.UnregisterCustomClassLayout("UWidgetStudioBase");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWidgetStudioEditor, WidgetStudioEditor)
