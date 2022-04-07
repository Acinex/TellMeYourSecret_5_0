// Copyright Acinex Games 2020

#include "CharacterUtil.h"

#include "TellMeYourSecret/Characters/Character/ClothComponent.h"

UClothComponent* UCharacterUtil::GetClothSlot(AActor* Actor, const EClothSlot Slot)
{
	TArray<UClothComponent*> Components;
	Actor->GetComponents<UClothComponent>(Components);

	for (UClothComponent* Component : Components)
	{
		if (Component->GetClothSlot() == Slot)
		{
			return Component;
		}
	}

	return nullptr;
}
