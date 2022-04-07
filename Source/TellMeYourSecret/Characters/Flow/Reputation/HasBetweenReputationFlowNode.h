// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "AbstractReputationCheckFlowNode.h"
#include "HasBetweenReputationFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Has Reputation Between"))
class TELLMEYOURSECRET_API UHasBetweenReputationFlowNode : public UAbstractReputationCheckFlowNode
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif

protected:
	UPROPERTY(EditAnywhere)
	int32 From;
	UPROPERTY(EditAnywhere)
	int32 To;

	virtual bool Check(const TWeakObjectPtr<UNonPlayerComponent>& NonPlayerComponent) const override;
};
