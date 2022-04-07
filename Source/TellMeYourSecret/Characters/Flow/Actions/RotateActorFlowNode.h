// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Flow/ActorFlowNode.h"

#include "RotateActorFlowNode.generated.h"

UCLASS(NotBlueprintable, meta=(DisplayName="Rotate Actor"))
class TELLMEYOURSECRET_API URotateActorFlowNode : public UActorFlowNode
{
	GENERATED_BODY()
public:
	explicit URotateActorFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR

	virtual FString GetNodeDescription() const override;

	virtual AActor* GetActorToFocus() override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category = "Target")
	FGameplayTagContainer TargetIdentityTags;
};
