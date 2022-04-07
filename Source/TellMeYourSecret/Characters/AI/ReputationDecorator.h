// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "TellMeYourSecret/Utils/NumericRelation.h"
#include "ReputationDecorator.generated.h"

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UReputationDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
    UPROPERTY(EditAnywhere)
    int32 Reputation;
    UPROPERTY(EditAnywhere)
    ENumericRelation NumericRelation;
};