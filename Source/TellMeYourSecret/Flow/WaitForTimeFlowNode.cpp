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
	UTimeManager* TimeManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTimeManager>();

	TimeManager->OnTimeChanged.AddDynamic(this, &UWaitForTimeFlowNode::TimeChanged);
	AddStatusReport(FString("It's ") + TimeManager->GetTimeAsText().ToString());
	TriggerFirstOutput(false);
}

void UWaitForTimeFlowNode::Cleanup()
{
	UTimeManager* TimeManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTimeManager>();

	TimeManager->OnTimeChanged.RemoveDynamic(this, &UWaitForTimeFlowNode::TimeChanged);
}

void UWaitForTimeFlowNode::TimeChanged(const int32 CurrentHour, const int32 CurrentMinute)
{
	ClearStatusReport();

	FStringFormatNamedArguments Args;
	Args.Add(TEXT("Hour"), CurrentHour);
	Args.Add(TEXT("Minute"), CurrentMinute);
	AddStatusReport(FString::Format(TEXT("It's {Hour}:{Minute}"), Args));
	
	if (CurrentHour >= Hour && CurrentMinute >= Minute)
	{
		TriggerOutput(TEXT("Completed"), true);
	}
}
