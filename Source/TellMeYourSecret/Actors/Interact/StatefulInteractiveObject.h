// Copyright Acinex Games 2020

#pragma once
#include "GameplayTagContainer.h"
#include "InteractiveObject.h"
#include "TellMeYourSecret/GameInstances/InteractiveObjectData.h"
#include "TellMeYourSecret/Model/InteractiveInterface.h"
#include "TellMeYourSecret/UMG/InteractWidget.h"
#include "StatefulInteractiveObject.generated.h"

class UInputSettings;
class ULockComponent;
class UInteractComponent;
class UInteractSubSystem;

UCLASS(BlueprintType)
class TELLMEYOURSECRET_API AStatefulInteractiveObject : public AInteractiveObject, public IInteractiveInterface
{
	GENERATED_BODY()

	friend class UInteractSubSystem;
public:
	virtual void OnConstruction(const FTransform& Transform) override;


	virtual void AnimateOn_Implementation(FLatentActionInfo LatentInfo) override;
	virtual void AnimateOff_Implementation(FLatentActionInfo LatentInfo) override;
	virtual void TurnOn_Implementation() override;
	virtual void TurnOff_Implementation() override;
	virtual void Load_Implementation(const FInteractiveObjectData& Saved) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetState() const { return bState; }


protected:
	/** Text to be displayed when the state is 'on' */
	UPROPERTY(EditAnywhere)
	FText OffTooltipText;
	/** Text to be displayed when the state is 'off' */
	UPROPERTY(EditAnywhere)
	FText OnTooltipText;
	/** Bound actors will be toggled together with this actor. */
	UPROPERTY(EditInstanceOnly)
	TSet<AStatefulInteractiveObject*> BoundActors;
	

	virtual FText GetTooltipText() const override;

	virtual void Use_Implementation(const FGameplayTagContainer Identity, FLatentActionInfo LatentInfo) override;
	virtual void Toggle(TArray<AStatefulInteractiveObject*> Visited, FLatentActionInfo LatentInfo);
	
	/** Specifies the default state */
	UPROPERTY(EditAnywhere, SaveGame, BlueprintReadWrite)
	bool bState;

	UPROPERTY(EditAnywhere)
	float AutoTurnOff;

private:
	FTimerHandle Handle;
	UFUNCTION()
	void AutoOff();
	
	void SetState(TArray<AStatefulInteractiveObject*> Visited);
};