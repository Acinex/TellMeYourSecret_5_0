// Copyright Acinex Games 2020

#pragma once

#include "InteractComponent.h"
#include "Components/TimelineComponent.h"
#include "TellMeYourSecret/Model/Direction.h"
#include "RotatingInteractComponent.generated.h"

class ADoorBase;
class UAudioComponent;

/**
 * Used to rotate SceneComponents.
 *
 * Add the Tag 'Rotate' to the child-components you want to rotate
 */
UCLASS(Blueprintable, ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API URotatingInteractComponent : public UInteractComponent
{
	GENERATED_BODY()
public:

	static const FName Wanted_Tag;

	// Sets default values for this component's properties
	URotatingInteractComponent();

	virtual void AnimateOn_Implementation(FLatentActionInfo LatentInfo) override;
	virtual void AnimateOff_Implementation(FLatentActionInfo LatentInfo) override;
	virtual void TurnOn_Implementation() override;
	virtual void TurnOff_Implementation() override;

protected:
	/** Direction in which the door shall open */
	UPROPERTY(EditAnywhere)
	EDirection Direction;
	/** Amount to rotate the door */
	UPROPERTY(EditAnywhere)
	float Degrees = 90.0F;

	/** Float curve asset to use when animating the door (Mandator) */
	UPROPERTY(EditAnywhere)
	UCurveFloat* AnimationCurve;

	UPROPERTY()
	UTimelineComponent* TimeLine;
	/** Sound to play when door opens */
	UPROPERTY(EditAnywhere)
	USoundBase* OpenSound;
	/** Sound to play when door was closed */
	UPROPERTY(EditAnywhere)
	USoundBase* CloseSound;

	virtual void  BeginPlay() override;
	virtual FName GetWantedTag() const override { return Wanted_Tag; }

private:
	UFUNCTION()
	void TimelineUpdate(const float Value);
	UFUNCTION()
	void OnTimelineFinished();

	void PlaySound(USoundBase* Sound) const;

	/** Declare delegate function to #TimelineUpdate() */
	FOnTimelineFloat TimelineFloat{};
	FOnTimelineEvent TimelineFinished{};
};
