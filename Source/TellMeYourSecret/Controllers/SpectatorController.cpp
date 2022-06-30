// Copyright Acinex Games 2020


#include "SpectatorController.h"

#include "FlowSubsystem.h"
#include "GameplayTagsManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TellMeYourSecret/Characters/NonPlayerComponent.h"


// Sets default values
ASpectatorController::ASpectatorController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpectatorController::Spectate(FString Name)
{
	const UFlowSubsystem* FlowSubsystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UFlowSubsystem>();
	const FGameplayTag Tag = FGameplayTag::RequestGameplayTag(FName(TEXT("Character.") + Name), false);
	TSet<UFlowComponent*> FlowComponents = FlowSubsystem->GetFlowComponentsByTag(Tag, UNonPlayerComponent::StaticClass());

	if (FlowComponents.Num() != 1)
	{
		return;
	}

	Spectated = FlowComponents[FSetElementId::FromInteger(0)]->GetOwner();
}

// Called when the game starts or when spawned
void ASpectatorController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpectatorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(Spectated))
	{
		const FVector ActorLocation = Spectated->GetActorLocation() + Rotation.RotateVector({0, 150.0F, Z});

		GetPawn()->SetActorLocation(ActorLocation);
	}
}

void ASpectatorController::Rotate(float X)
{
	Rotation.Yaw -= X * 5;
	
	if (X != 0 && IsValid(Spectated))
	{
		FRotator FindLookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), Spectated->GetActorLocation());

		FindLookAtRotation.Pitch = ControlRotation.Pitch;
		FindLookAtRotation.Roll = ControlRotation.Roll;
		SetControlRotation(FindLookAtRotation);
	}
}

void ASpectatorController::MoveUp(float X)
{
	Z = FMath::Clamp(Z + X, -70, 70);
}

void ASpectatorController::Faster()
{
	UGameplayStatics::SetGlobalTimeDilation(this, UGameplayStatics::GetGlobalTimeDilation(this) + 0.5);
}

void ASpectatorController::Slower()
{
	UGameplayStatics::SetGlobalTimeDilation(this, UGameplayStatics::GetGlobalTimeDilation(this) - 0.5);
}

void ASpectatorController::DefaultSpeed()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 1);
}

void ASpectatorController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MouseX", this, &ASpectatorController::AddYawInput);
	InputComponent->BindAxis("MouseY", this, &ASpectatorController::AddPitchInput);

	InputComponent->BindAxis("MoveForward", this, &ASpectatorController::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &ASpectatorController::Rotate);

	InputComponent->BindKey(EKeys::Add, IE_Pressed, this, &ASpectatorController::Faster);
	InputComponent->BindKey(EKeys::Subtract, IE_Pressed, this, &ASpectatorController::Slower);
	InputComponent->BindKey(EKeys::NumPadZero, IE_Pressed, this, &ASpectatorController::DefaultSpeed);
}
