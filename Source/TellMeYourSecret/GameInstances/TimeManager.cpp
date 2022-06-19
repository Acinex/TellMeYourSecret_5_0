// Copyright Acinex Games 2020

#include "TimeManager.h"
#include "Kismet/KismetMathLibrary.h"

void UTimeManager::AddSecond(const float Delta)
{
	DateTime += UKismetMathLibrary::FromSeconds(Delta);
	OnTimeChanged.Broadcast(GetHour(), GetMinute());
}

FText UTimeManager::GetTimeAsText() const
{
	FFormatOrderedArguments Arguments;

	FString Hour = DateTime.GetHour() < 10 ? "0" : "";
	Hour.Append(FString::FromInt(DateTime.GetHour()));

	FString Minute = DateTime.GetMinute() < 10 ? "0" : "";
	Minute.Append(FString::FromInt(DateTime.GetMinute()));

	Arguments.Add(FFormatArgumentValue(FText::FromString(Hour)));
	Arguments.Add(FFormatArgumentValue(FText::FromString(Minute)));

	return FText::Format(FTextFormat::FromString(TEXT("{0}:{1}")), Arguments);
}

void UTimeManager::AddHour(const float Delta)
{
	DateTime += UKismetMathLibrary::FromHours(Delta);
	OnTimeChanged.Broadcast(GetHour(), GetMinute());
}

int32 UTimeManager::GetHour() const
{
	return DateTime.GetHour();
}

int32 UTimeManager::GetMinute() const
{
	return DateTime.GetMinute();
}

bool UTimeManager::IsTime(const int32 Hour, const int32 Minute, const int32 Second) const
{
	const bool bIsHour   = Hour == -1 || DateTime.GetHour() == Hour;
	const bool bIsMinute = Minute == -1 || DateTime.GetMinute() == Minute;
	const bool bIsSecond = Second == -1 || DateTime.GetSecond() == Second;

	return bIsHour && bIsMinute && bIsSecond;
}

int32 UTimeManager::GetDayOfYear() const
{
	return DateTime.GetDayOfYear();
}

void UTimeManager::FreezeTime(const bool bFreeze)
{
	bFrozenTime = bFreeze;
}

FTimespan UTimeManager::GetTimeOfDay() const
{
	return DateTime.GetTimeOfDay();
}

void UTimeManager::SetTimeOfDay(const int32 Time)
{
	DateTime -= DateTime.GetTimeOfDay();
	DateTime += FTimespan(Time * ETimespan::TicksPerSecond);
	OnTimeChanged.Broadcast(GetHour(), GetMinute());
}

float UTimeManager::GetTime() const
{
	return DateTime.ToUnixTimestamp();
}

void UTimeManager::SetTime(const float Time)
{
	DateTime = FDateTime::FromUnixTimestamp(Time);
	OnTimeChanged.Broadcast(GetHour(), GetMinute());
}

void UTimeManager::Tick(const float DeltaTime)
{
	DateTime += FTimespan(DeltaTime * ETimespan::TicksPerSecond * InGameSecondsPerSecond);
	OnTimeChanged.Broadcast(GetHour(), GetMinute());
}

TStatId UTimeManager::GetStatId() const
{
	return TStatId();
}
