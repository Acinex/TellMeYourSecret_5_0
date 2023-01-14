// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TheBackroomsGameInstance.generated.h"

class UFlowAsset;

/**
 * 
 */
UCLASS()
class THEBACKROOMSLT_API UTheBackroomsGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void LoadRootFlow(UFlowAsset* Asset);
};
