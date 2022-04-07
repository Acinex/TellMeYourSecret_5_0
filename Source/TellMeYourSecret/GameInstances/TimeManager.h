// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TimeManager.generated.h"

UCLASS()
class TELLMEYOURSECRET_API UTimeManager : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InGameSecondsPerSecond = 60.0F;

	UFUNCTION(BlueprintCallable)
	void AddSecond(float Delta);
	UFUNCTION(BlueprintCallable)
	FText GetTimeAsText() const;
	UFUNCTION(BlueprintCallable)
	void AddHour(const float Delta);
	UFUNCTION(BlueprintPure)
	int32 GetHour() const;
	UFUNCTION(BlueprintPure)
	int32 GetMinute() const;
	UFUNCTION(BlueprintCallable)
	bool IsTime(int32 Hour = -1, int32 Minute = -1, int32 Second = -1) const;
	UFUNCTION(BlueprintCallable)
	int GetDayOfYear() const;

	UFUNCTION(BlueprintCallable)
	void FreezeTime(bool bFreeze);

	UFUNCTION(BlueprintPure)
	FTimespan GetTimeOfDay() const;
	UFUNCTION(BlueprintCallable)
	void SetTimeOfDay(int32 Time);

	UFUNCTION(BlueprintCallable)
	float GetTime() const;
	UFUNCTION(BlueprintCallable)
	void SetTime(const float Time);

protected:
	virtual void Tick(float DeltaTime) override;

	virtual bool    IsTickableInEditor() const override { return true; }
	virtual TStatId GetStatId() const override;
	virtual bool    IsTickable() const override { return !bFrozenTime; }
	virtual UWorld* GetTickableGameObjectWorld() const override { return GetWorld(); }

private:
	FDateTime DateTime;
	float     LastTime = 0.0F;

	bool bFrozenTime;
};
