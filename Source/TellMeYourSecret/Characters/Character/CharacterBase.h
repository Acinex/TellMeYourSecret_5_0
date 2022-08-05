// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UClothComponent;
UCLASS()
class TELLMEYOURSECRET_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

	friend class UCharacterAnimationInstance;
public:
	ACharacterBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly)
	UAudioComponent* Voice;

	UPROPERTY(Category=Cloth, VisibleAnywhere, BlueprintReadOnly)
	UClothComponent* Pants;
	UPROPERTY(Category=Cloth, VisibleAnywhere, BlueprintReadOnly)
	UClothComponent* Underpants;
	UPROPERTY(Category=Cloth, VisibleAnywhere, BlueprintReadOnly)
	UClothComponent* Bra;
	UPROPERTY(Category=Cloth, VisibleAnywhere, BlueprintReadOnly)
	UClothComponent* Socks;
	UPROPERTY(Category=Cloth, VisibleAnywhere, BlueprintReadOnly)
	UClothComponent* Shoes;
	UPROPERTY(Category=Cloth, VisibleAnywhere, BlueprintReadOnly)
	UClothComponent* Top;
	UPROPERTY(Category=Cloth, VisibleAnywhere, BlueprintReadOnly)
	UClothComponent* Dress;
	UPROPERTY(Category=Cloth, VisibleAnywhere, BlueprintReadOnly)
	UClothComponent* Hat;
	UPROPERTY(Category=Cloth, VisibleAnywhere, BlueprintReadOnly)
	UClothComponent* Gloves;

	UPROPERTY(EditDefaultsOnly)
	float IKInterpSpeed = 0.1;
	UPROPERTY(BlueprintReadOnly)
	FVector IKOffsetLeftFoot;
	UPROPERTY(BlueprintReadOnly)
	FVector IKOffsetRightFoot;
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EPhysicalSurface> LeftFootSurface;
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EPhysicalSurface> RightFootSurface;

	UPROPERTY(EditDefaultsOnly)
	FName LeftFootSocket = TEXT("lFoot");
	UPROPERTY(EditDefaultsOnly)
	FName RightFootSocket = TEXT("rFoot");

	UPROPERTY()
	float IKTraceDistance;
	UPROPERTY()
	float Scale;

private:
	FVector FootTrace(FName Socket, TEnumAsByte<EPhysicalSurface>& OutSurface) const;
};
