// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "TellMeYourSecret/Characters/Character/ClothSlot.h"
#include "TellMeYourSecret/Flow/ActorFlowNode.h"

#include "ChangeClothFlowComponent.generated.h"

UCLASS(NotBlueprintable, meta=(DisplayName="Change Cloth"))
class TELLMEYOURSECRET_API UChangeClothFlowComponent : public UActorFlowNode
{
	GENERATED_BODY()

public:
	explicit UChangeClothFlowComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
#endif

protected:
	UPROPERTY(EditAnywhere)
	TMap<EClothSlot, TSoftObjectPtr<USkeletalMesh>> Clothes;
};
