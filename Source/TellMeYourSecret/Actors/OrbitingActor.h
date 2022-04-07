#pragma once

#include "GameFramework/Actor.h"
#include "OrbitingActor.generated.h"

class UTimeManager;

UCLASS(Blueprintable)
class TELLMEYOURSECRET_API AOrbitingActor : public AActor
{
	GENERATED_BODY()
public:
	explicit AOrbitingActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
	UCurveFloat* PitchCurve;
	UPROPERTY(EditAnywhere)
	UCurveFloat* YawCurve;
	UPROPERTY(EditAnywhere)
	UCurveFloat* RollCurve;

	void Rotate(const float Time);

private:
	UPROPERTY()
	UTimeManager* TimeManager;
};
