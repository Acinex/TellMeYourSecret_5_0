// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "NavLinkCustomComponent.h"
#include "DoorNavLink.generated.h"

class ADoorBase;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UDoorNavLink : public UNavLinkCustomComponent
{
	GENERATED_BODY()
public:
	UDoorNavLink();

	virtual void BeginPlay() override;
	void     Complete(AActor* Agent);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/** resume normal path following */
	UFUNCTION(BlueprintCallable, Category="AI|Navigation")
	void ResumePathFollowing(AActor* Agent);

private:
	UPROPERTY()
	ADoorBase* Door;
	
	UPROPERTY()
	TMap<AActor*, FVector> PendingAgents;

	int32 ID;

	UFUNCTION()
	void NotifySmartLinkReached(UNavLinkCustomComponent* LinkComp, UObject* PathingAgent, const FVector& DestPoint);
	
	
	UFUNCTION()
	void OpenDoor(AActor* Agent, const FVector& Destination);
	
};

UCLASS()
class UDoorLinkLatentAction : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	AActor* Agent;
	UPROPERTY()
	UDoorNavLink* DoorLink;

	UFUNCTION()
	void ContinueMove();
};
