#include "NonPlayerCharacter.h"

#include "NonPlayerCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "NonPlayerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANonPlayerCharacter::ANonPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NonPlayerComponent = CreateDefaultSubobject<UNonPlayerComponent>(TEXT("Non Player"));

	GetCharacterMovement()->bUseRVOAvoidance = true;
}

void ANonPlayerCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!AIControllerClass)
	{
		AIControllerClass = ANonPlayerCharacterController::StaticClass();
	}
}

int32 ANonPlayerCharacter::GetReputation() const
{
	return NonPlayerComponent->GetReputation();
}
