// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "InteractComponent.h"
#include "AnimateInteractComponent.generated.h"

/**
 * Animate the SkeletalMeshes.
 *
 * Add the Tag 'Animate' to the child-components you want to animate
 */
UCLASS(Blueprintable, ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API UAnimateInteractComponent : public UInteractComponent
{
    GENERATED_BODY()

public:
    static const FName Wanted_Tag;

    virtual void AnimateOn_Implementation(FLatentActionInfo LatentInfo) override;
    virtual void AnimateOff_Implementation(FLatentActionInfo LatentInfo) override;
    virtual void TurnOn_Implementation() override;
    virtual void TurnOff_Implementation() override;

protected:
    virtual FName GetWantedTag() const override { return Wanted_Tag; }
};
