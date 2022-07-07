// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "ActorFlowNode.h"
#include "Play3DSoundFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Play 3D Sound"))
class TELLMEYOURSECRET_API UPlay3DSoundFlowNode : public UActorFlowNode
{
	GENERATED_BODY()
public:
	explicit UPlay3DSoundFlowNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual bool    IsParametersValid() const override;

	virtual UObject* GetAssetToEdit() override;
#endif

protected:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<USoundBase> Sound;

	virtual void PreloadContent() override;
};
