// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "SelfController.h"
#include "GameFramework/Actor.h"
#include "SpectatorController.generated.h"

UCLASS()
class TELLMEYOURSECRET_API ASpectatorController : public ASelfController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpectatorController();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	UFUNCTION(Exec)
	void Spectate(FString Name);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FRotator Rotation;
	float Z;

private:
	UPROPERTY()
	AActor* Spectated;

	UFUNCTION()
	void Rotate(float X);
	UFUNCTION()
	void MoveUp(float X);
	UFUNCTION()
	void Faster();
	UFUNCTION()
	void Slower();
	UFUNCTION()
	void DefaultSpeed();
};
