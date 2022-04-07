#pragma once
#include "GameFramework/Character.h"
#include "ReputationSystem.h"
#include "NonPlayerCharacter.generated.h"

class UClothComponent;
class UNonPlayerComponent;
class UBehaviorTree;
UCLASS(Abstract, BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API ANonPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	explicit ANonPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	int32 GetReputation() const;

	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

protected:
	UPROPERTY()
	UReputationSystem* ReputationSystem = nullptr;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly)
	UNonPlayerComponent* NonPlayerComponent;

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
};
