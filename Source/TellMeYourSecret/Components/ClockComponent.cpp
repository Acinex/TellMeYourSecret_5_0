// Copyright Acinex Games 2020

#include "ClockComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/TimeManager.h"

UClockComponent::UClockComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor                     = true;
}

void UClockComponent::BeginPlay()
{
	Super::BeginPlay();
	TimeManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTimeManager>();

	HourHand   = FindHand(TEXT("Hour"));
	MinuteHand = FindHand(TEXT("Minute"));
}

UMeshComponent* UClockComponent::FindHand(const FName Tag) const
{
	TArray<UActorComponent*> ActorComponents = GetOwner()->GetComponentsByTag(UMeshComponent::StaticClass(), Tag);
	if (ActorComponents.Num())
	{
		return Cast<UMeshComponent>(ActorComponents[0]);
	}

	return nullptr;
}

void UClockComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TimeManager)
	{
		const float Minutes = TimeManager->GetMinute() / 60.0F;
		const float Hours   = (TimeManager->GetHour() + Minutes) / 24.0F;

		if (IsValid(MinuteHand))
		{
			MinuteHand->SetWorldRotation({Minutes * 360.0F, 0, 0});
		}
		if (IsValid(HourHand))
		{
			HourHand->SetWorldRotation({Hours * 360.0F, 0, 0});
		}
	}
}
