// Copyright Acinex Games 2020


#include "WaitForTimeFlowNode.h"

#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/TimeManager.h"

UWaitForTimeFlowNode::UWaitForTimeFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Time");
#endif

	OutputPins.Add({TEXT("Completed"), TEXT("Called once the Time has passed or is exactly matched")});
}

void UWaitForTimeFlowNode::ExecuteInput(const FName& PinName)
{
	TimeManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTimeManager>();

	if (Hour <= TimeManager->GetHour() && Minute <= TimeManager->GetMinute())
	{
		TriggerFirstOutput(false);
		TriggerOutput(TEXT("Completed"), true);
		return;
	}

	TimeManager->OnTimeChanged.AddDynamic(this, &UWaitForTimeFlowNode::TimeChanged);
	TriggerFirstOutput(false);
}

#if WITH_EDITOR
FString UWaitForTimeFlowNode::GetStatusString() const
{
	if (IsValid(TimeManager))
	{
		return TimeManager->GetTimeAsText().ToString();
	}

	return "";
}
#endif

void UWaitForTimeFlowNode::Cleanup()
{
	TimeManager->OnTimeChanged.RemoveDynamic(this, &UWaitForTimeFlowNode::TimeChanged);
}

void UWaitForTimeFlowNode::TimeChanged(const int32 CurrentHour, const int32 CurrentMinute)
{
	FStringFormatNamedArguments Args;
	Args.Add(TEXT("Hour"), CurrentHour);
	Args.Add(TEXT("Minute"), CurrentMinute);

	if (CurrentHour >= Hour && CurrentMinute >= Minute)
	{
		TriggerOutput(TEXT("Completed"), true);
	}
}
