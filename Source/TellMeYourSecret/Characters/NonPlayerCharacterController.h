// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"

#include "NonPlayerCharacterController.generated.h"

class ANonPlayerCharacter;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API ANonPlayerCharacterController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
