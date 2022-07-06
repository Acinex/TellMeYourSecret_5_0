// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Flow/NonPlayerComponentFlowNode.h"
#include "AbstractMontageFlowNode.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class TELLMEYOURSECRET_API UAbstractMontageFlowNode : public UNonPlayerComponentFlowNode
{
	GENERATED_BODY()

public:
	explicit UAbstractMontageFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual bool IsParametersValid() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category=Animation)
	TSoftObjectPtr<UAnimMontage> Montage;

	UPROPERTY(EditAnywhere, Category=Animation)
	FName StartSectionName;

	virtual void Cleanup() override;

	virtual void OnLoad_Implementation() override;
	virtual void OnSave_Implementation() override;

	virtual void OnComplete()
	{
	}

	virtual void PreloadContent() override;

	void PlayAnimation();
	void Stop();

	virtual void OnAnimNotify(const FName Name);

private:
	UPROPERTY(SaveGame)
	float Position = -1.0F;
	int32 MontageInstanceID;

	UFUNCTION(BlueprintCallable)
	void AnimationFinished();

	UFUNCTION()
	void OnPlayMontageNotifyBegin(FName Name, const FBranchingPointNotifyPayload& BranchingPointPayload);
};
