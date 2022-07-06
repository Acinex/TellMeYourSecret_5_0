// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Flow/ActorFlowNode.h"
#include "ChangeMaterialFlowNode.generated.h"

USTRUCT()
struct FMaterialArray
{
	GENERATED_BODY()

	/** Material per MaterialIndex */
	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<UMaterial>> Materials;
};

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Change Material"))
class TELLMEYOURSECRET_API UChangeMaterialFlowNode : public UActorFlowNode
{
	GENERATED_BODY()

public:
	explicit UChangeMaterialFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

protected:
	/** Material-Array per Component in that specific order */
	UPROPERTY(EditAnywhere)
	TArray<FMaterialArray> Materials;

	virtual void PreloadContent() override;
};
