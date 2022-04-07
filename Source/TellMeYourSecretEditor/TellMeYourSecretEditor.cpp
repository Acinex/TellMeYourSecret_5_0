// Copyright Acinex Games 2020.

#include "TellMeYourSecretEditor.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "Modules/ModuleManager.h"
#include "Quests/AssetTypeActions_QuestFlowAsset.h"

class FLevelEditorModule;

void FTellMeYourSecretEditor::StartupModule()
{
	RegisterAssets();
}

void FTellMeYourSecretEditor::ShutdownModule()
{
	UnregisterAssets();
}

void FTellMeYourSecretEditor::RegisterAssets()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	const TSharedRef<IAssetTypeActions> FlowAssetActions = MakeShareable(new FAssetTypeActions_QuestFlowAsset());
	RegisteredAssetActions.Add(FlowAssetActions);
	AssetTools.RegisterAssetTypeActions(FlowAssetActions);
}

void FTellMeYourSecretEditor::UnregisterAssets()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (const TSharedRef<IAssetTypeActions>& TypeAction : RegisteredAssetActions)
		{
			AssetTools.UnregisterAssetTypeActions(TypeAction);
		}
	}

	RegisteredAssetActions.Empty();
}

IMPLEMENT_MODULE(FTellMeYourSecretEditor, TellMeYourSecretEditor)
