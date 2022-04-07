// Copyright Acinex Games 2020.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TellMeYourSecretGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API ATellMeYourSecretGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ATellMeYourSecretGameModeBase();

	virtual void BeginPlay() override;

	virtual void RestartPlayer(AController* NewPlayer) override;

	virtual void StartPlay() override;
	
};
