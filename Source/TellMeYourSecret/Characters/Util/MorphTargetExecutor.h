#pragma once
#include "MorphTargetChange.h"

#include "MorphTargetExecutor.generated.h"

class UCharacterComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishStep);

UCLASS(NotBlueprintable)
class UMorphTargetExecutor : public UObject
{
	GENERATED_BODY()
public:
	explicit UMorphTargetExecutor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void AddMorphTargetChange(UCharacterComponent* CharacterComponent, const FMorphTargetChange MorphTargetChange);

	virtual void Stop() const;

	UPROPERTY()
	FFinishStep OnStepFinished;
private:
	void ExecuteMorphTargetChange(UCharacterComponent* CharacterComponent, FMorphTargetExecution* TargetExecution);
};
