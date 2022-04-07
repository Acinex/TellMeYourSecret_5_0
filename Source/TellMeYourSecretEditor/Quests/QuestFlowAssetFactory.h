// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "QuestFlowAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRETEDITOR_API UQuestFlowAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	explicit UQuestFlowAssetFactory(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
