// Copyright Acinex Games 2020

#include "ChangeClothFlowComponent.h"

#include "TellMeYourSecret/Characters/Character/ClothComponent.h"

UChangeClothFlowComponent::UChangeClothFlowComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Action");
#endif
}

void UChangeClothFlowComponent::ExecuteInput(const FName& PinName)
{
	const AActor* Actor = FindActor();
	if (!Actor)
	{
		return Finish();
	}

	TInlineComponentArray<UClothComponent*> ClothComponents(Actor);

	for (const TTuple<EClothSlot, TSoftObjectPtr<USkeletalMesh>> Tuple : Clothes)
	{
		for (UClothComponent* ClothComponent : ClothComponents)
		{
			if (ClothComponent->GetClothSlot() == Tuple.Key)
			{
				ClothComponent->SetSkeletalMesh(Tuple.Value.LoadSynchronous());
			}
		}
	}

	TriggerFirstOutput(true);
}

#if WITH_EDITOR
FString UChangeClothFlowComponent::GetNodeDescription() const
{
	const UEnum* Enum = StaticEnum<EClothSlot>();
	FString ClothString;

	for (const TTuple<EClothSlot, TSoftObjectPtr<USkeletalMesh>> Tuple : Clothes)
	{
		ClothString.Append(LINE_TERMINATOR).Append(Enum->GetNameByValue(static_cast<int64>(Tuple.Key)).ToString())
		           .Append(": ").Append(Tuple.Value.IsNull() ? "none" : Tuple.Value.GetAssetName());
	}

	return Super::GetNodeDescription() + ClothString;
}
#endif
