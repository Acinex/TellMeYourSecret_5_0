// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClockComponent.generated.h"

class UTimeManager;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TELLMEYOURSECRET_API UClockComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UClockComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UMeshComponent* HourHand;
	UPROPERTY()
	UMeshComponent* MinuteHand;

	UPROPERTY()
	UTimeManager* TimeManager;

	UMeshComponent* FindHand(FName Tag) const;
};
