// Copyright Acinex Games 2020

#include "TimeRangeDecorator.h"

#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/TimeManager.h"

bool UTimeRangeDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    UTimeManager* TimeManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTimeManager>();

    const int32 ActualHour   = TimeManager->GetHour();
    const int32 ActualMinute = TimeManager->GetMinute();

    const int32 ActualTime = ActualHour * 60 + ActualMinute;
    const int32 StartTime  = StartHour * 60 + StartMinute;
    const int32 EndTime    = EndHour * 60 + EndMinute;

    if (StartTime < EndTime)
    {
        return ActualTime >= StartTime && ActualTime < EndTime;
    }

    return ActualTime >= StartTime || ActualTime < EndTime;
}
