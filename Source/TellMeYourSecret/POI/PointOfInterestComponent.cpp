// Copyright Acinex Games 2020

#include "PointOfInterestComponent.h"

#include "PoIManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UPointOfInterestComponent::UPointOfInterestComponent()
{
}

FVector UPointOfInterestComponent::FindRandomSpot_Implementation()
{
	UBoxComponent* BoxComponent = GetOwner()->FindComponentByClass<UBoxComponent>();

	if (IsValid(BoxComponent))
	{
		return UKismetMathLibrary::RandomPointInBoundingBox(GetOwner()->GetActorLocation(), BoxComponent->GetUnscaledBoxExtent());
	}

	return GetOwner()->GetActorLocation();
}

const FGameplayTagContainer UPointOfInterestComponent::GetIdentifier_Implementation() const
{
	return Identity;
}

// Called when the game starts
void UPointOfInterestComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetGameInstance(this)->GetSubsystem<UPoIManager>()->Register(this);
}
