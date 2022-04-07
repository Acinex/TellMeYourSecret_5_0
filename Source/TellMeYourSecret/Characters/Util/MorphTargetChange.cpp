// Copyright Acinex Games 2020

#include "MorphTargetChange.h"

float FMorphTargetExecution::GetCurrentValue() const
{
	return CurrentValue;
}

float FMorphTargetExecution::GetTargetValue() const
{
	return MorphTargetChange.Value;
}

float FMorphTargetExecution::GetRate() const
{
	return 1 / 30.0F;
}

void FMorphTargetExecution::Step() const
{
	const float FrameRate = 1/30.0F;
	
	// 1 / (0,2 / 0,033)
	CurrentValue = FMath::Min(CurrentValue + MorphTargetChange.Value / (MorphTargetChange.Time / FrameRate), MorphTargetChange.Value);
}

FName FMorphTargetExecution::GetName() const
{
	return MorphTargetChange.Name;
}
