// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "StatusReportFlowNode.h"
#include "PlaySoundFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Play 2D sound"))
class TELLMEYOURSECRET_API UPlaySoundFlowNode : public UStatusReportFlowNode
{
	GENERATED_BODY()
public:
	explicit UPlaySoundFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual bool IsParametersValid() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category = "Identity")
	FGameplayTagContainer IdentityTags;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USoundBase> Sound;
};
