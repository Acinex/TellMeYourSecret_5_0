#pragma once
#include "Engine/DataTable.h"

#include "MorphTargetChange.generated.h"

USTRUCT()
struct FMorphTargetChange
{
	GENERATED_BODY()
	/** Name of the MorphTarget to change */
	UPROPERTY(EditAnywhere)
	FName Name;
	/** To which value to change */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "-1.0", ClampMax = "1.0"))
	float Value;
	/** Time in seconds to animate to the value. 0 means instant */
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float Time;
	/** How many steps to make */
	UPROPERTY(EditAnywhere)
	uint8 Steps = 30;

	friend bool operator==(const FMorphTargetChange& Lhs, const FMorphTargetChange& RHS)
	{
		return Lhs.Name == RHS.Name;
	}

	friend bool operator!=(const FMorphTargetChange& Lhs, const FMorphTargetChange& RHS)
	{
		return !(Lhs == RHS);
	}
};

USTRUCT(BlueprintType)
struct TELLMEYOURSECRET_API FLetterMorphTarget : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FMorphTargetChange> MorphTargetChanges;

};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FHashMeIfYouCan& Thing);
#else // optimize by inlining in shipping and development builds
FORCEINLINE uint32 GetTypeHash(const FMorphTargetChange& Thing)
{
	const uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FMorphTargetChange));
	return Hash;
}
#endif

struct FMorphTargetExecution
{
	mutable float CurrentValue = 0.0F;

	mutable int8 ID = 0;

	FTimerHandle TimerHandle;

	explicit FMorphTargetExecution(const FMorphTargetChange InMorphTargetChange)
	{
		MorphTargetChange = InMorphTargetChange;
	}

	float GetCurrentValue() const;
	float GetTargetValue() const;
	float GetRate() const;

	void  Step() const;
	FName GetName() const;

private:
	FMorphTargetChange MorphTargetChange;
};
