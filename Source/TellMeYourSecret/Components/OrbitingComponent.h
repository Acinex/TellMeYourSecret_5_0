// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "FlowComponent.h"
#include "OrbitingComponent.generated.h"


class UTimeManager;
UCLASS(ClassGroup=(TMYS), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API UOrbitingComponent : public UFlowComponent
{
	GENERATED_BODY()

public:
	UOrbitingComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Rotate(const float Time) const;

protected:
	UPROPERTY(EditAnywhere)
	UCurveFloat* PitchCurve;
	UPROPERTY(EditAnywhere)
	UCurveFloat* YawCurve;
	UPROPERTY(EditAnywhere)
	UCurveFloat* RollCurve;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UTimeManager* TimeManager;
};
