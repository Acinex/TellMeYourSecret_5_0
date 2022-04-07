// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Navigation/NavLinkProxy.h"
#include "DoorLink.generated.h"

class ADoorBase;
/**
 * 
 */
UCLASS(Blueprintable)
class TELLMEYOURSECRET_API ADoorLink : public ANavLinkProxy
{
	GENERATED_BODY()

public:
	explicit ADoorLink(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	void     Complete(AActor* Agent);

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	ADoorBase* Door;

	UFUNCTION()
	void OpenDoor(AActor* Agent, const FVector& Destination);

	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY()
	TMap<AActor*, FVector> PendingAgents;

	int32 ID;
};

UCLASS()
class UDoorLinkLatentAction : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	AActor* Agent;
	UPROPERTY()
	ADoorLink* DoorLink;

	UFUNCTION()
	void ContinueMove();
};
