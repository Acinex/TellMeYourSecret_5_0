// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "AbstractMontageFlowNode.h"
#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "PlayAnimationMontageFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Play Animation Montage"))
class TELLMEYOURSECRET_API UPlayAnimationMontageFlowNode : public UAbstractMontageFlowNode
{
	GENERATED_BODY()

public:
	explicit UPlayAnimationMontageFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual bool          SupportsContextPins() const override { return true; }
	virtual TArray<FName> GetContextOutputs() override { return Notifies; }
	virtual UObject* GetAssetToEdit() override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category=Notify)
	TArray<FName> Notifies;

	virtual void OnComplete() override;

	virtual void OnAnimNotify(FName Name) override;
};
