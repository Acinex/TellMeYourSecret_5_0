// Copyright Acinex Games 2020

#include "StatusReportFlowNode.h"


UStatusReportFlowNode::UStatusReportFlowNode(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

#if WITH_EDITOR
bool UStatusReportFlowNode::GetDynamicTitleColor(FLinearColor& OutColor) const
{
	if (!IsParametersValid())
	{
		OutColor = FLinearColor::Red;
		return true;
	}

	return Super::GetDynamicTitleColor(OutColor);
}

FString UStatusReportFlowNode::GetStatusString() const
{
	FString Result;

#if WITH_EDITOR

	for (const FString String : Log)
	{
		if (!Result.IsEmpty())
		{
			Result.Append(LINE_TERMINATOR);
		}

		Result.Append(String);
	}
#endif

	return Result;
}
#endif

void UStatusReportFlowNode::AddStatusReport(const FString Message)
{
#if WITH_EDITOR
	Log.Add(Message);
#endif
}

void UStatusReportFlowNode::ClearStatusReport()
{
#if WITH_EDITOR
	Log.Empty();
#endif
}
