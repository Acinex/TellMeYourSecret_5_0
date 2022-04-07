// Copyright Acinex Games 2020

#pragma once
#include "InteractComponent.h"
#include "HeightAdjustComponent.generated.h"

/**
* Used to set the relative location for SceneComponents.
*
* Add the Tag 'Height' to the child-components you want to adjust
*/
UCLASS(ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API UHeightAdjustComponent : public UInteractComponent
{
    GENERATED_BODY()
public:
    static const FName Wanted_Tag;

protected:
    /** Define the height for every Component ordered by hierarchy */
    UPROPERTY(EditAnywhere)
    TArray<float> Heights{0.0F};

    virtual void AnimateOn_Implementation(FLatentActionInfo LatentInfo) override;
    virtual void AnimateOff_Implementation(FLatentActionInfo LatentInfo) override;
    virtual void TurnOn_Implementation() override;
    virtual void TurnOff_Implementation() override;

    virtual FName GetWantedTag() const override { return Wanted_Tag; }

private:
    void UpdateHeight() const;
};
