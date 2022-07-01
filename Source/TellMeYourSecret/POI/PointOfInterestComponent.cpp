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

void UPointOfInterestComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UPointOfInterestComponent, Identity))
	{
		UpdateActorLabel();
	}
}

void UPointOfInterestComponent::UpdateActorLabel()
{
	TArray<FGameplayTag> Tags;
	Identity.GetGameplayTagArray(Tags);

	for (FGameplayTag Tag : Tags)
	{
		FString Label = Tag.GetTagName().ToString();

		if (Label.StartsWith("POI.") || Label.StartsWith("POV."))
		{
			GetOwner()->SetActorLabel(Label);
			return;
		}
	}
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
