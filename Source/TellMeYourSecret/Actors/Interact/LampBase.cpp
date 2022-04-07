// Copyright Acinex Games 2020

#include "LampBase.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TellMeYourSecret/Utils/CompletablePendingLatentAction.h"

ALampBase::ALampBase()
{
	bCanBeUsed     = false;
	OffTooltipText = NSLOCTEXT("Interactive", "Lamp.Off", "Press {0} to turn off");
	OnTooltipText  = NSLOCTEXT("Interactive", "Lamp.On", "Press {0} to turn on");
}

void ALampBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetColor(Color);
}

void ALampBase::AnimateOn_Implementation(FLatentActionInfo LatentInfo)
{
	FCompletablePendingLatentAction* Action = new FCompletablePendingLatentAction(LatentInfo);

	GetWorld()->GetLatentActionManager().AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	TurnOn();
	Action->Complete();
}

void ALampBase::AnimateOff_Implementation(FLatentActionInfo LatentInfo)
{
	FCompletablePendingLatentAction* Action = new FCompletablePendingLatentAction(LatentInfo);

	GetWorld()->GetLatentActionManager().AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, Action);
	TurnOff();
	Action->Complete();
}

void ALampBase::TurnOn_Implementation()
{
	Super::TurnOn_Implementation();
	TurnOn();
}

void ALampBase::TurnOff_Implementation()
{
	Super::TurnOff_Implementation();
	TurnOff();
}

void ALampBase::SetColor(const FColor NewColor)
{
	for (ULightComponent* Light : GetLights())
	{
		Light->SetLightColor(NewColor);
	}

	if (Material && !EmissiveColorName.IsNone())
	{
		Material->SetVectorParameterValue(EmissiveColorName, FLinearColor(Color));
	}

	Color = NewColor;
}

TSet<ULightComponent*> ALampBase::GetLights() const
{
	TArray<USceneComponent*> ChildComponents;
	RootComponent->GetChildrenComponents(true, ChildComponents);

	TSet<ULightComponent*> Lights;
	for (USceneComponent* Component : ChildComponents)
	{
		ULightComponent* Light = Cast<ULightComponent>(Component);
		if (Light)
		{
			Lights.Add(Light);
		}
	}

	return Lights;
}

void ALampBase::TurnOn() const
{
	for (ULightComponent* Light : GetLights())
	{
		Light->SetIntensity(OnIntensity);
	}

	if (Material && !EmissiveName.IsNone())
	{
		Material->SetScalarParameterValue(EmissiveName, OnEmissive);
	}
}

void ALampBase::TurnOff() const
{
	for (ULightComponent* Light : GetLights())
	{
		Light->SetIntensity(OffIntensity);
	}

	if (Material && !EmissiveName.IsNone())
	{
		Material->SetScalarParameterValue(EmissiveName, OffEmissive);
	}
}
