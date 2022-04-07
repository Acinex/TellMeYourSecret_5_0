// Copyright Acinex Games 2020

#pragma once
#include "TellMeYourSecret/Actors/Interact/StatefulInteractiveObject.h"
#include "DoorBase.generated.h"

class UInteractComponent;

UCLASS(BlueprintType)
class TELLMEYOURSECRET_API ADoorBase : public AStatefulInteractiveObject
{
    GENERATED_BODY()

public:
    ADoorBase();

    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* Door;
};
