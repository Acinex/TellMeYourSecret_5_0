// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "SpawnParams.h"
#include "StatusReportFlowNode.h"

#include "SpawnActorFlowNode.generated.h"

class UFlowComponent;
class USpawnComponent;
/**
 * 
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Spawn Actor"))
class TELLMEYOURSECRET_API USpawnActorFlowNode : public UStatusReportFlowNode
{
	GENERATED_BODY()
public:
	explicit USpawnActorFlowNode(const FObjectInitializer& ObjectInitializer);

	virtual void ExecuteInput(const FName& PinName) override;
#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn Point")
	FGameplayTagContainer IdentityTags;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FSpawnParams SpawnParams;

	UPROPERTY(SaveGame)
	TArray<FTransform> ActorTransforms;
	UPROPERTY(SaveGame)
	int32 SpawnersNum;

	virtual void OnSave_Implementation() override;
	virtual void OnLoad_Implementation() override;

private:
	TArray<TWeakObjectPtr<USpawnComponent>> SpawnComponents;
	UFUNCTION()
	void CheckSpawns(UFlowComponent* Component);

	bool Spawn();
	void SpawnOneActor(UFlowComponent* Component, int32& SpawnCount);
};
