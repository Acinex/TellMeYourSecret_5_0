// Copyright Acinex Games 2020

#include "PlayerCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "TellMeYourSecret/Characters/NonPlayerCharacter.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"
#include "TellMeYourSecret/Characters/Character/CharacterComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TellMeYourSecret/Smartphone/Smartphone.h"
#include "TellMeYourSecret/Actors/Interact/StatefulInteractiveObject.h"
#include "TellMeYourSecret/Smartphone/Screen/ScreenWidget.h"
#include "TellMeYourSecret/Smartphone/SmartphoneMesh.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/UMG/HeadsUpDisplay.h"

class IDlgDialogueParticipant;

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 300.f;
	GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0F;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 60.0F;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	SelfieCam = CreateDefaultSubobject<UCameraComponent>(TEXT("SelfieCam"));
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	SmartphoneMesh = CreateDefaultSubobject<USmartphoneMesh>(TEXT("Smartphone"));
	SmartphoneScreen = CreateDefaultSubobject<UWidgetComponent>(TEXT("SmartphoneScreen"));
	CharacterComponent = CreateDefaultSubobject<UCharacterComponent>(TEXT("CharacterComponent"));

	SmartphoneMesh->SetupAttachment(GetMesh());
	SmartphoneScreen->SetupAttachment(SmartphoneMesh);
	SpringArm->SetupAttachment(GetMesh());
	FirstPersonCamera->SetupAttachment(GetMesh(), TEXT("head"));
	ThirdPersonCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	MainCamera->SetupAttachment(SmartphoneMesh);
	SelfieCam->SetupAttachment(SmartphoneMesh);

	SpringArm->TargetArmLength = DefaultArmLength; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	ThirdPersonCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	ThirdPersonCamera->bAutoActivate = true;
	MainCamera->bAutoActivate = false;
	SelfieCam->bAutoActivate = false;
	FirstPersonCamera->bAutoActivate = false;
	FirstPersonCamera->bUsePawnControlRotation = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Smartphone = UGameplayStatics::GetGameInstance(this)->GetSubsystem<USmartphone>();

	if (SmartphoneScreen)
	{
		UScreenWidget* ScreenWidget = Cast<UScreenWidget>(SmartphoneScreen->GetUserWidgetObject());
		if (Smartphone)
		{
			Smartphone->SetScreen(ScreenWidget);
		}
	}

	DefaultArmLength = SpringArm->TargetArmLength;
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &APlayerCharacter::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &APlayerCharacter::ZoomOut);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::ToggleCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::ToggleUnCrouch);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::UnSprint);
	PlayerInputComponent->BindAction("ToggleCamera", IE_Pressed, this, &APlayerCharacter::ToggleCamera);
	PlayerInputComponent->BindAction("ToggleSmartphone", IE_Pressed, this, &APlayerCharacter::ToggleSmartphone);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("MouseX", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("MouseY", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

bool APlayerCharacter::KFootTrace(const FName SocketName, const float Distance, float& OutHitOffset, FVector& OutLocation) const
{
	const float CapsuleHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	const float ActorZ = GetActorLocation().Z;

	FVector SocketLocation = GetMesh()->GetSocketLocation(SocketName);
	SocketLocation.Z = ActorZ - CapsuleHalfHeight / 2.0F;
	FVector End = SocketLocation - FVector(0, 0, Distance);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult, SocketLocation, End, ECC_Visibility, Params);

	OutHitOffset = 0.0F;

	if (Hit)
	{
		OutHitOffset = (HitResult.ImpactPoint.Z - (ActorZ - CapsuleHalfHeight)) * -1.0F;
		OutLocation = HitResult.ImpactPoint;
	}

	return Hit;
}

void APlayerCharacter::ToggleSmartphoneCamera()
{
	if (bIsUsingSmartphoneCamera)
	{
		bSelfieCamera = !bSelfieCamera;
	}

	bIsUsingSmartphoneCamera = true;

	GetFirstPersonCamera()->Deactivate();

	if (bSelfieCamera)
	{
		MainCamera->Deactivate();
		SelfieCam->Activate();
	}
	else
	{
		SelfieCam->Deactivate();
		MainCamera->Activate();
	}
}

void APlayerCharacter::DeactivateSmartphoneCamera()
{
	bIsUsingSmartphoneCamera = false;
	SelfieCam->Deactivate();
	MainCamera->Deactivate();
	GetFirstPersonCamera()->Activate();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UE_LOG(LogTellMeYourSecret, Log, TEXT("PossessedBy PlayerCharacter"))
	if (HeadsUpDisplayClass)
	{
		APlayerController* PlayerController = GetController<APlayerController>();
		if (PlayerController)
		{
			HeadsUpDisplay = Cast<UHeadsUpDisplay>(CreateWidget(PlayerController, HeadsUpDisplayClass));
			HeadsUpDisplay->AddToViewport();
			if (Smartphone)
			{
				Smartphone->SetHUD(HeadsUpDisplay);
			}
		}
	}
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector Location;
	FRotator Rotation;
	GetController()->GetPlayerViewPoint(Location, Rotation);

	if (bIsFirstPerson)
	{
		FRotator ActorRotation = GetActorRotation();
		FRotator ControlRotation = GetControlRotation();
		ActorRotation.Normalize();
		ControlRotation.Normalize();

		if (ControlRotation.Yaw < -90 && ActorRotation.Yaw > 90)
		{
			ControlRotation.Yaw += 360;
		}
		if (ActorRotation.Yaw < -90 && ControlRotation.Yaw > 90)
		{
			ActorRotation.Yaw += 360;
		}

		float Distance = (ControlRotation - ActorRotation).Yaw;

		if (FMath::Abs(Distance) > ControlRotationThreshold)
		{
			FRotator TargetRotation = ActorRotation;
			TargetRotation.Yaw = ControlRotation.Yaw;
			if (Distance > 0)
			{
				TargetRotation.Yaw -= ControlRotationThreshold;
			}
			else
			{
				TargetRotation.Yaw += ControlRotationThreshold;
			}

			SetActorRotation(FMath::Lerp(ActorRotation, TargetRotation, DeltaSeconds * 10));
		}
	}

	const FVector End = Location + Rotation.Vector() * (150.0F + SpringArm->TargetArmLength);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECC_Visibility, Params);

	AActor* HitActor = Hit.GetActor();
	if (VisibleActor && VisibleActor != HitActor)
	{
		if (AInteractiveObject* InteractiveObject = Cast<AInteractiveObject>(VisibleActor))
		{
			InteractiveObject->HideTooltip();
		}
	}

	VisibleActor = HitActor;

	if (!VisibleActor)
	{
		return;
	}

	AInteractiveObject* InteractiveObject = Cast<AInteractiveObject>(VisibleActor);
	if (InteractiveObject)
	{
		InteractiveObject->ShowTooltip();
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APlayerCharacter::Interact()
{
	if (!VisibleActor)
	{
		return;
	}

	AInteractiveObject* InteractiveObject = Cast<AInteractiveObject>(VisibleActor);
	if (IsValid(InteractiveObject))
	{
		InteractiveObject->Interact(FindComponentByClass<UCharacterComponent>()->IdentityTags, FLatentActionInfo());
	}

	const UNonPlayerComponent* NonPlayerComponent = VisibleActor->FindComponentByClass<UNonPlayerComponent>();
	if (IsValid(NonPlayerComponent))
	{
		NonPlayerComponent->RequestDialogue();
	}
}

void APlayerCharacter::ToggleCrouch()
{
	Super::Crouch();
}

void APlayerCharacter::ToggleUnCrouch()
{
	Super::UnCrouch();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APlayerCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= 3;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APlayerCharacter::UnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed /= 3;
}

void APlayerCharacter::ToggleCamera()
{
	GetActiveCamera()->Deactivate();
	bIsFirstPerson = !bIsFirstPerson;
	GetActiveCamera()->Activate();
	GetCharacterMovement()->bOrientRotationToMovement = !bIsFirstPerson;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController && PlayerController->PlayerCameraManager)
	{
		if (bIsFirstPerson)
		{
			PlayerController->PlayerCameraManager->ViewPitchMax = 45.0F;
			PlayerController->PlayerCameraManager->ViewPitchMin = -40.0F;
		}
		else
		{
			PlayerController->PlayerCameraManager->ViewPitchMax = 89.9f;
			PlayerController->PlayerCameraManager->ViewPitchMin = -89.9f;
		}
	}
}

void APlayerCharacter::ToggleSmartphone()
{
	bIsUsingSmartphoneCamera = false;
	bSelfieCamera = false;
	bIsShowingSmartphone = !bIsShowingSmartphone;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (bIsShowingSmartphone)
	{
		Smartphone->Show();
		SmartphoneMesh->SetVisibility(true, true);
		bWasFirstPerson = bIsFirstPerson;

		if (!bIsFirstPerson)
		{
			ToggleCamera();
		}

		GetController()->SetControlRotation(UKismetMathLibrary::FindLookAtRotation(FirstPersonCamera->GetComponentToWorld().GetLocation(), SmartphoneMesh->GetComponentToWorld().GetLocation()));

		FInputModeGameAndUI Mode;
		Mode.SetWidgetToFocus(SmartphoneScreen->GetSlateWidget());
		PlayerController->SetInputMode(Mode);
	}
	else
	{
		Smartphone->Hide();
		SmartphoneMesh->SetVisibility(false, true);
		if (!bWasFirstPerson)
		{
			ToggleCamera();
		}

		const FInputModeGameOnly Mode;
		PlayerController->SetInputMode(Mode);
	}

	PlayerController->bShowMouseCursor = bIsShowingSmartphone;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APlayerCharacter::ZoomIn()
{
	if (bIsFirstPerson)
	{
		return;
	}

	SpringArm->TargetArmLength = FMath::Max(SpringArm->TargetArmLength - 20.0F, 0.0F);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void APlayerCharacter::ZoomOut()
{
	if (bIsFirstPerson)
	{
		return;
	}

	SpringArm->TargetArmLength = FMath::Min(SpringArm->TargetArmLength + 20.0F, DefaultArmLength);
}

void APlayerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void APlayerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void APlayerCharacter::TurnAtRate(const float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(const float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveForward(const float Value)
{
	if (!Controller || Value == 0.0f)
	{
		return;
	}

	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	if (Value > 0 && bIsFirstPerson)
	{
		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Normalize();

		SetActorRotation({0, ControlRotation.Yaw, 0});
	}
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveRight(const float Value)
{
	if (!Controller || Value == 0.0f)
	{
		return;
	}

	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, Value);
}
