#pragma once
#include "Character/CharacterBase.h"
#include "GameFramework/Character.h"
#include "NonPlayerCharacter.generated.h"

class UClothComponent;
class UNonPlayerComponent;
class UBehaviorTree;
UCLASS(Abstract, BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API ANonPlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	explicit ANonPlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnConstruction(const FTransform& Transform) override;

	int32 GetReputation() const;

protected:
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly)
	UNonPlayerComponent* NonPlayerComponent;
};
