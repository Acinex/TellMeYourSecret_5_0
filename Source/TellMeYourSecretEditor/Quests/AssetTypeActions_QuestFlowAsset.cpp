#include "AssetTypeActions_QuestFlowAsset.h"

#include "FlowEditorModule.h"
#include "QuestFlowAssetFactory.h"
#include "TellMeYourSecret/Quests/QuestFlowAsset.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_QuestFlowAsset"

FText FAssetTypeActions_QuestFlowAsset::GetName() const
{
	return LOCTEXT("AssetTypeActions_QuestFlowAsset", "Quest Asset");
}

uint32 FAssetTypeActions_QuestFlowAsset::GetCategories()
{
	return FFlowEditorModule::FlowAssetCategory;
}

UClass* FAssetTypeActions_QuestFlowAsset::GetSupportedClass() const
{
	return UQuestFlowAsset::StaticClass();
}

void FAssetTypeActions_QuestFlowAsset::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UQuestFlowAsset* FlowAsset = Cast<UQuestFlowAsset>(*ObjIt))
		{
			const FFlowEditorModule* FlowModule = &FModuleManager::LoadModuleChecked<FFlowEditorModule>("FlowEditor");
			FlowModule->CreateFlowAssetEditor(Mode, EditWithinLevelEditor, FlowAsset);
		}
	}
}

#undef LOCTEXT_NAMESPACE
