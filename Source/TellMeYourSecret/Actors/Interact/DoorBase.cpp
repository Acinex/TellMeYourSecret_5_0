// Copyright Acinex Games 2020

#include "DoorBase.h"

#include "TellMeYourSecret/Log.h"
#include "Components/StaticMeshComponent.h"
#include "TellMeYourSecret/Components/DoorNavLink.h"

ADoorBase::ADoorBase()
{
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));

	DoorNavLink = CreateDefaultSubobject<UDoorNavLink>(TEXT("NavLink"));

	RootComponent = Root;
	Door->SetupAttachment(Root);

	OffTooltipText = NSLOCTEXT("Interactive", "Door.Off", "Press {0} to close");
	OnTooltipText = NSLOCTEXT("Interactive", "Door.On", "Press {0} to open");
}

void ADoorBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (!InteractComponents.Num())
		UE_LOG(LogTellMeYourSecret, Warning, TEXT("Door %s has no interact-component, so it can't be used"), *GetName())
}
