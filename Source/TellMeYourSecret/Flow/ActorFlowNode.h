// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "StatusReportFlowNode.h"
#include "ActorFlowNode.generated.h"

class UFlowComponent;
/**
 * 
 */
UCLASS(Abstract, NotBlueprintable)
class TELLMEYOURSECRET_API UActorFlowNode : public UStatusReportFlowNode
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category = Identifier)
	FGameplayTagContainer IdentityTags;

	AActor* FindActor();
	AActor* FindActor(FGameplayTagContainer Tags);
};
