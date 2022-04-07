// Copyright Acinex Games 2020
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "DayDecorator.generated.h"

UCLASS()
class TELLMEYOURSECRET_API UDayDecorator : public UBTDecorator
{
    GENERATED_BODY()
public:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 DayOfWeek = -1;
};
