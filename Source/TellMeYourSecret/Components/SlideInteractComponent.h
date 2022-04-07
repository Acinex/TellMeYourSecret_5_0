// Copyright Acinex Games 2020

#pragma once
#include "InteractComponent.h"
#include "Components/TimelineComponent.h"

#include "SlideInteractComponent.generated.h"

class UTimelineComponent;
/**
* Used to slide SceneComponents.
*
* Add the Tag 'Slide' to the child-components you want to slide
*/
UCLASS( Blueprintable, ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent) )
class TELLMEYOURSECRET_API USlideInteractComponent : public UInteractComponent
{
    GENERATED_BODY()

public:
    static const FName Wanted_Tag;

    USlideInteractComponent();

    virtual void BeginPlay() override;

    virtual void AnimateOn_Implementation(FLatentActionInfo LatentInfo) override;
    virtual void AnimateOff_Implementation(FLatentActionInfo LatentInfo) override;
    virtual void TurnOn_Implementation() override;
    virtual void TurnOff_Implementation() override;

protected:
    /** Distance to move */
    UPROPERTY(EditAnywhere)
    float Distance;
    /** Float curve asset to use when animating the door (Mandatory) */
    UPROPERTY(EditAnywhere)
    UCurveFloat* AnimationCurve;
    /** In which direction to slide */
    UPROPERTY(EditAnywhere)
    TEnumAsByte<EAxis::Type> Axis;
    UPROPERTY()
    UTimelineComponent* TimeLine;

    virtual FName GetWantedTag() const override { return Wanted_Tag; }

private:
    UFUNCTION()
    void TimelineUpdate(const float Value);


    /** Declare delegate function to #TimelineUpdate() */
    FOnTimelineFloat TimelineFloat{};
};
