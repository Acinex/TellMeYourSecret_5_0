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
	FStringFormatNamedArguments Args;
	Args.Add(TEXT("Hour"), Hour);
	Args.Add(TEXT("Minute"), Minute);
	FString Status = FString::Format(TEXT("Waiting for {Hour}:{Minute}"), Args);

	if (IsValid(TimeManager))
	{
		return Status + " -- " + TimeManager->GetTimeAsText().ToString();
	}

	return Status;
}
#endif

void UWaitForTimeFlowNode::Cleanup()
{
	if (TimeManager)
		TimeManager->OnTimeChanged.RemoveDynamic(this, &UWaitForTimeFlowNode::TimeChanged);
}

void UWaitForTimeFlowNode::TimeChanged(const int32 CurrentHour, const int32 CurrentMinute)
{
	if (CurrentHour >= Hour && CurrentMinute >= Minute)
	{
		TriggerOutput(TEXT("Completed"), true);
	}
}
