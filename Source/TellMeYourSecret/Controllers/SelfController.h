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

    virtual void OnPossess(APawn* InPawn) override;

private:
    void ShowMenu();
};
