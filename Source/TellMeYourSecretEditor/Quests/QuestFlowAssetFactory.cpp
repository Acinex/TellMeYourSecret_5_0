// Copyright Acinex Games 2020


#include "QuestFlowAssetFactory.h"

#include "FlowEditor/Public/Graph/FlowGraph.h"
#include "TellMeYourSecret/Quests/QuestFlowAsset.h"

UQuestFlowAssetFactory::UQuestFlowAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UQuestFlowAsset::StaticClass();

	bCreateNew = true;
	bEditorImport = false;
	bEditAfterNew = true;
}

UObject* UQuestFlowAssetFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UQuestFlowAsset* NewFlow = NewObject<UQuestFlowAsset>(InParent, Class, Name, Flags | RF_Transactional, Context);
	UFlowGraph::CreateGraph(NewFlow);
	return NewFlow;
}
