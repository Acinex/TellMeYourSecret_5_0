// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TellMeYourSecret/GameInstances/InteractiveObjectData.h"
#include "InteractiveObject.generated.h"

class UInputSettings;
class UInteractWidget;
class ULockComponent;
class UInteractComponent;
/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API AInteractiveObject : public AActor
{
	GENERATED_BODY()
	friend class UInteractSubSystem;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer IdentityTags;

	virtual void OnConstruction(const FTransform& Transform) override;

	void ShowTooltip();
	void HideTooltip();
	UFUNCTION(BlueprintCallable, meta=(Latent, LatentInfo="LatentInfo"))
	bool Interact(const FGameplayTagContainer Identity, FLatentActionInfo LatentInfo);

	bool IsLocked(const FGameplayTagContainer Identity) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Load(const FInteractiveObjectData& Saved);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FInteractiveObjectData Save();

protected:
	UPROPERTY()
	TArray<UInteractComponent*> InteractComponents;
	UPROPERTY(SaveGame)
	ULockComponent* LockComponent;
	/** If set to true, the player can toggle this by looking and hit the specific key */
	UPROPERTY(EditAnywhere)
	bool bCanBeUsed = true;

	UPROPERTY()
	UInteractSubSystem* SubSystem;
	/** Text to be displayed when the user looks at it */
	UPROPERTY(EditAnywhere)
	FText TooltipText;

	virtual void BeginPlay() override;
	FORCEINLINE FText GetText() const;
	virtual FText GetTooltipText() const;

	UFUNCTION(BlueprintNativeEvent)
	void Use(const FGameplayTagContainer Identity, FLatentActionInfo LatentInfo);

	UInteractWidget* GetWidget();

private:
	UPROPERTY()
	UInteractWidget* Widget;

	UPROPERTY()
	UInputSettings* InputSettings;
};
