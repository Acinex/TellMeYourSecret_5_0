// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SelfController.generated.h"

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API ASelfController : public APlayerController
{
    GENERATED_BODY()
public:
    ASelfController();

    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

private:
    void ShowMenu();
};
