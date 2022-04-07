// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "AbstractReputationCheckFlowNode.h"
#include "HasLowerReputationFlowNode.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta=(DisplayName="Has Lower Reputation"))
class TELLMEYOURSECRET_API UHasLowerReputationFlowNode : public UAbstractReputationCheckFlowNode
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif

protected:
	UPROPERTY(EditAnywhere)
	int32 Reputation;

	virtual bool Check(const TWeakObjectPtr<UNonPlayerComponent>& NonPlayerComponent) const override;
};
