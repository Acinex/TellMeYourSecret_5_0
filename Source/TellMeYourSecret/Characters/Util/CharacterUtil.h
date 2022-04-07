// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Character/ClothSlot.h"

#include "CharacterUtil.generated.h"

class UClothComponent;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UCharacterUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UClothComponent* GetClothSlot(AActor* Actor, EClothSlot Slot);
};
