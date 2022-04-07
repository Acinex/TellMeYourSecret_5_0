// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "SetBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API USetBlackboardValue : public UBTService_BlackboardBase
{
    GENERATED_BODY()
protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    UPROPERTY(EditAnywhere)
    TSubclassOf<UBlackboardKeyType> KeyClass;

    UPROPERTY(EditAnywhere)
    bool Boolean;
    UPROPERTY(EditAnywhere)
    float Float;
    UPROPERTY(EditAnywhere)
    int32 Integer;
    UPROPERTY(EditAnywhere)
    uint8 Enum;
    UPROPERTY(EditAnywhere)
    FString String;
    UPROPERTY(EditAnywhere)
    FName Name;
    UPROPERTY(EditAnywhere)
    UObject* Object;
    UPROPERTY(EditAnywhere)
    UClass* Class;
    UPROPERTY(EditAnywhere)
    FVector Vector;
    UPROPERTY(EditAnywhere)
    FRotator Rotator;
};
