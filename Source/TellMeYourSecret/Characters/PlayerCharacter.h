// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Smartphone/SmartphonePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCharacterComponent;
class USmartphone;
class UHeadsUpDisplay;
class UWidgetComponent;
class USmartphoneMesh;

UCLASS()
class TELLMEYOURSECRET_API APlayerCharacter : public ACharacter, public ISmartphonePlayer
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void BeginPlay() override;

	virtual void ToggleSmartphone() override;
	virtual void ToggleSmartphoneCamera() override;
	virtual void DeactivateSmartphoneCamera() override;

	virtual void PossessedBy(AController* NewController) override;
	
	USmartphoneMesh* GetSmartphone() const { return SmartphoneMesh; }

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return SpringArm; }
	FORCEINLINE UCameraComponent*    GetThirdPersonCamera() const { return ThirdPersonCamera; }
	FORCEINLINE UCameraComponent*    GetFirstPersonCamera() const { return FirstPersonCamera; }
	FORCEINLINE bool                 IsShowingSmartphone() const { return bIsShowingSmartphone; }
	FORCEINLINE bool                 IsFirstPerson() const { return bIsFirstPerson; }

protected:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float DefaultArmLength = 150.0F;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* MainCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* SelfieCam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USmartphoneMesh* SmartphoneMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* SmartphoneScreen;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UCharacterComponent* CharacterComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHeadsUpDisplay> HeadsUpDisplayClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHeadsUpDisplay* HeadsUpDisplay;

	UPROPERTY()
	USmartphone* Smartphone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFirstPerson;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool  bIsShowingSmartphone;
	bool  bWasFirstPerson;
	bool  bSelfieCamera = false;
	bool  bIsUsingSmartphoneCamera;
	float ControlRotationThreshold = 20.0F;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	UFUNCTION(BlueprintCallable)
	bool KFootTrace(FName SocketName, float Distance, float& OutHitOffset, FVector& OutLocation) const;

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE UCameraComponent* GetActiveCamera() const { return bIsFirstPerson ? GetFirstPersonCamera() : GetThirdPersonCamera(); };

private:
	UPROPERTY()
	AActor* VisibleActor;

	void Interact();

	void ToggleCrouch();
	void ToggleUnCrouch();

	void Sprint();
	void UnSprint();

	void ToggleCamera();

	void ZoomIn();
	void ZoomOut();
};
