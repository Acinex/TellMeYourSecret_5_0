// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "TellMeYourSecret/Characters/Util/MorphTargetChange.h"

#include "MorphTargetFlowNode.generated.h"

class UMorphTargetExecutor;
/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Morph Target"))
class TELLMEYOURSECRET_API UMorphTargetFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()
public:
	explicit UMorphTargetFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual bool IsParametersValid() const override;
	virtual FString GetStatusString() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, meta = (TitleProperty = "Name"))
	TSet<FMorphTargetChange> MorphTargets;

	/** Clear all morph targets before applying the new ones */
	UPROPERTY(EditAnywhere)
	bool bClearMorphTargets;

	UFUNCTION()
	virtual void FinishStep();

#if WITH_EDITORONLY_DATA
	/** Is shown above this node to identify the morph result */
	UPROPERTY(EditAnywhere)
	FString Title;
#endif

private:
	int8 Counter;
	UPROPERTY()
	UMorphTargetExecutor* Executor;
};
