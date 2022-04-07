// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "TimeRangeDecorator.generated.h"

/**
* 
*/
UCLASS()
class TELLMEYOURSECRET_API UTimeRangeDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
    UPROPERTY(EditAnywhere)
    int32 StartHour = 0;
    UPROPERTY(EditAnywhere)
    int32 StartMinute = 0;
    UPROPERTY(EditAnywhere)
    int32 EndHour = 24;
    UPROPERTY(EditAnywhere)
    int32 EndMinute = 0;
};
