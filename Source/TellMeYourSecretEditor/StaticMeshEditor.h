// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "ActorActionUtility.h"
#include "StaticMeshEditor.generated.h"

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRETEDITOR_API UStaticMeshEditor : public UActorActionUtility
{
	GENERATED_BODY()

protected:
	UFUNCTION(CallInEditor)
	void ConvertIntoInstance(FVector Location, bool bAtCenter, bool bCreateWithMultipleMeshes);
	UFUNCTION(CallInEditor)
	void MergeInstances();
	UFUNCTION(CallInEditor)
	void SplitInstance();

private:
	static UWorld* TryGetWorld();
};
