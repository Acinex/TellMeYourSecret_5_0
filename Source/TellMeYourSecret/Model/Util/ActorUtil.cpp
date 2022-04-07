#include "ActorUtil.h"

#include "Kismet/KismetMathLibrary.h"

void FActorUtil::Rotate(AActor* Target, const float Degrees, const EAxis::Type Axis)
{
    if (!Target)
    {
        return;
    }

    FRotator Rotator;

    switch (Axis)
    {
    case EAxis::None: return;
    case EAxis::X:
        Rotator = {0.0F, 0.0F, Degrees};
        break;
    case EAxis::Y:
        Rotator = {Degrees, 0.0F, 0.0F};
        break;
    case EAxis::Z:
        Rotator = {0.0F, Degrees, 0.0F};
        break;
    }

    Target->SetActorRotation(Rotator);
}

void FActorUtil::Rotate(USceneComponent* Target, const float Degrees, const EAxis::Type Axis)
{
    if (!Target)
    {
        return;
    }

    FRotator Rotator;

    switch (Axis)
    {
    case EAxis::None: return;
    case EAxis::X:
        Rotator = {0.0F, 0.0F, Degrees};
        break;
    case EAxis::Y:
        Rotator = {Degrees, 0.0F, 0.0F};
        break;
    case EAxis::Z:
        Rotator = {0.0F, Degrees, 0.0F};
        break;
    }

    Target->SetRelativeRotation(Rotator);
}

void FActorUtil::Slide(USceneComponent* Target, const float Value, const EAxis::Type Axis)
{
    if (!Target)
    {
        return;
    }

    FVector NewLocation;

    switch (Axis)
    {
    case EAxis::None: return;
    case EAxis::X:
        NewLocation = {Value, 0.0F, 0.0F};
        break;
    case EAxis::Y:
        NewLocation = {0.0F, Value, 0.0F};
        break;
    case EAxis::Z:
        NewLocation = {0.0F, 0.0F, Value};
        break;
    };

    Target->SetRelativeLocation(NewLocation);
}
