#pragma once
#include "TellMeYourSecret/Model/Direction.h"

class TELLMEYOURSECRET_API FActorUtil
{
public:
    static void Rotate(AActor* Target, const float Degrees, const EAxis::Type Axis);
    static void Rotate(USceneComponent* Target, const float Degrees, const EAxis::Type Axis);

    static void Slide(USceneComponent* Target, const float Value, const EAxis::Type Axis);
};
