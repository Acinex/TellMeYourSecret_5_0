// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "ActorFlowNode.h"
#include "MoveActorFlowNode.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="Move Actor"))
class TELLMEYOURSECRET_API UMoveActorFlowNode : public UActorFlowNode, public FTickableGameObject
{
	GENERATED_BODY()
public:
	explicit UMoveActorFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;
#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif
	virtual void Tick(float DeltaTime) override;

	virtual bool    IsTickable() const override { return bTickable; }
	virtual TStatId GetStatId() const override;

protected:
	UPROPERTY(EditAnywhere)
	UCurveFloat* Curve;
	UPROPERTY(EditAnywhere)
	FVector Location;

private:
	FTimerHandle Handle;
	float        Time;
	FVector      Start;
	FVector      Difference;

	bool bTickable;
};
