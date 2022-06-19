// Copyright Acinex Games 2020

#include "StatefulInteractiveObject.h"

#include "TellMeYourSecret/Characters/Character/CharacterComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Components/InteractComponent.h"
#include "TellMeYourSecret/Components/LockComponent.h"
#include "TellMeYourSecret/GameInstances/InteractSubSystem.h"

void AStatefulInteractiveObject::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const TArray<AStatefulInteractiveObject*> Visited;
	SetState(Visited);
}

void AStatefulInteractiveObject::Use_Implementation(const FGameplayTagContainer Identity, FLatentActionInfo LatentInfo)
{
	const TArray<AStatefulInteractiveObject*> Visited;
	Toggle(Visited, LatentInfo);

	GetWorldTimerManager().ClearTimer(Handle);
	
	if(AutoTurnOff)
	{
		GetWorldTimerManager().SetTimer(Handle, this, &AStatefulInteractiveObject::AutoOff, AutoTurnOff, false);
	}
}

void AStatefulInteractiveObject::AnimateOn_Implementation(const FLatentActionInfo LatentInfo)
{
	if (!InteractComponents.Num())
	{
		return;
	}

	for (UInteractComponent* InteractComponent : InteractComponents)
	{
		Execute_AnimateOn(InteractComponent, LatentInfo);
	}
}

void AStatefulInteractiveObject::AnimateOff_Implementation(const FLatentActionInfo LatentInfo)
{
	if (!InteractComponents.Num())
	{
		return;
	}

	for (UInteractComponent* InteractComponent : InteractComponents)
	{
		Execute_AnimateOff(InteractComponent, LatentInfo);
	}
}

void AStatefulInteractiveObject::TurnOn_Implementation()
{
	if (!InteractComponents.Num())
	{
		return;
	}

	for (UInteractComponent* InteractComponent : InteractComponents)
	{
		Execute_TurnOn(InteractComponent);
	}
}

void AStatefulInteractiveObject::TurnOff_Implementation()
{
	if (!InteractComponents.Num())
	{
		return;
	}

	for (UInteractComponent* InteractComponent : InteractComponents)
	{
		Execute_TurnOff(InteractComponent);
	}
}

void AStatefulInteractiveObject::Load_Implementation(const FInteractiveObjectData& Saved)
{
	Super::Load_Implementation(Saved);

	if (GetState())
	{
		Execute_TurnOn(this);
	}
	else
	{
		Execute_TurnOff(this);
	}
}

FText AStatefulInteractiveObject::GetTooltipText() const
{
	return bState ? OffTooltipText : OnTooltipText;
}

void AStatefulInteractiveObject::Toggle(TArray<AStatefulInteractiveObject*> Visited, FLatentActionInfo LatentInfo)
{
	if (Visited.Contains(this))
	{
		return;
	}

	Visited.Add(this);

	if (!GetState())
	{
		Execute_AnimateOn(this, LatentInfo);
	}
	else
	{
		Execute_AnimateOff(this, LatentInfo);
	}

	bState = !bState;

	if (SubSystem)
	{
		SubSystem->Interacted(GetName(), bState);
	}

	if (HasActorBegunPlay())
	{
		GetWidget()->SetText(GetText());
	}

	for (AStatefulInteractiveObject* Actor : BoundActors)
	{
		if (Actor)
		{
			Actor->Toggle(Visited, LatentInfo);
		}
	}
}

void AStatefulInteractiveObject::AutoOff()
{
	const TArray<AStatefulInteractiveObject*> Visited;
	const FLatentActionInfo LatentInfo;
	Toggle(Visited, LatentInfo);
}

void AStatefulInteractiveObject::SetState(TArray<AStatefulInteractiveObject*> Visited)
{
	if (Visited.Contains(this))
	{
		return;
	}

	if (GetState())
	{
		Execute_TurnOn(this);
	}
	else
	{
		Execute_TurnOff(this);
	}

	Visited.Add(this);

	for (AInteractiveObject* Actor : BoundActors)
	{
		if (AStatefulInteractiveObject* Stateful = Cast<AStatefulInteractiveObject>(Actor))
		{
			Stateful->bState = GetState();

			if (GetState())
			{
				Execute_TurnOn(Stateful);
			}
			else
			{
				Execute_TurnOff(Stateful);
			}
		}
	}
}
