// Fill out your copyright notice in the Description page of Project Settings.


#include "TheBackroomsGameInstance.h"
#include "FlowAsset.h"
#include "FlowSubSystem.h"

void UTheBackroomsGameInstance::LoadRootFlow(UFlowAsset* Asset)
{
	UFlowSubsystem* SubSystem = GetSubsystem<UFlowSubsystem>();
	SubSystem->LoadRootFlow(this, Asset, Asset->GetName());
}
