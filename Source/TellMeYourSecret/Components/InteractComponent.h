// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TellMeYourSecret/Model/InteractiveInterface.h"

#include "InteractComponent.generated.h"

class UInteractWidget;
class UTellMeYourSecretGameInstance;

UCLASS()
class TELLMEYOURSECRET_API UInteractComponent : public UActorComponent, public IInteractiveInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	virtual FName GetWantedTag() const { return NAME_None; }

	/** Find all components of the owner which contains the wanted Tag */
	template <class T>
	TArray<T*> GetTaggedComponents() const
	{
		TArray<T*> TaggedComponents;
		TArray<T*> Components;

		GetOwner()->GetComponents<T, FDefaultAllocator>(Components, true);

		for (T* ActorComponent : Components)
		{
			if (ActorComponent->ComponentHasTag(GetWantedTag()))
			{
				TaggedComponents.Add(ActorComponent);
			}
		}

		return TaggedComponents;
	}
};
