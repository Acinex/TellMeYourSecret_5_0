// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "SitDownStandUpFlowNode.generated.h"

class UApproachComponent;
UENUM()
enum class ESitDownStandUpFlowExecutionState : uint8
{
	None,
	Moving,
	SitDown,
	Idle,
	StandUp
};

/**
 * 
 */
UCLASS(meta=(DisplayName="Sit Down / Stand Up"))
class TELLMEYOURSECRET_API USitDownStandUpFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()

public:
	explicit USitDownStandUpFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

	virtual void FixNode(UEdGraphNode* NewGraph) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual FString GetStatusString() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category=Animation)
	TSoftObjectPtr<UAnimMontage> SitDown;
	UPROPERTY(EditAnywhere, Category=Animation)
	FName SitDownSection;

	UPROPERTY(EditAnywhere, Category=Animation)
	TSoftObjectPtr<UAnimSequenceBase> Idle;

	UPROPERTY(EditAnywhere, Category=Animation)
	TSoftObjectPtr<UAnimMontage> StandUp;
	UPROPERTY(EditAnywhere, Category=Animation)
	FName StandUpSection;

	UPROPERTY(EditAnywhere, Category=Identifier)
	FGameplayTagContainer ChairTags;

	virtual void OnLoad_Implementation() override;

	virtual void PreloadContent() override;

private:
	UPROPERTY(SaveGame)
	ESitDownStandUpFlowExecutionState State = ESitDownStandUpFlowExecutionState::None;

	UPROPERTY(SaveGame)
	TWeakObjectPtr<UApproachComponent> ApproachComponent;

	bool Approach();
	void DoStandUp();
	void ApplyIdle();

	UFUNCTION()
	void IsSitting();
	UFUNCTION()
	void IsStanding();

	UFUNCTION()
	void Approached();
};
