// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "InteractiveObjectData.h"
#include "TellMeYourSecret/Model/Save/TmysSaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TellMeYourSecret/GameInstances/SaveGameAware.h"

#include "InteractSubSystem.generated.h"

class AInteractiveObject;
class ULockComponent;

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API UInteractSubSystem : public UGameInstanceSubsystem, public ISaveGameAware
{
	GENERATED_BODY()
public:
	void Register(AInteractiveObject* Object);
	void Interacted(const FString Name, const bool bIsOn);

	UFUNCTION(BlueprintPure)
	AInteractiveObject* FindObject(const FGameplayTagContainer& Identity, const EGameplayContainerMatchType MatchType) const;

private:
	TMultiMap<FGameplayTag, TWeakObjectPtr<AInteractiveObject>> Registry;
	UPROPERTY()
	TSet<TWeakObjectPtr<AInteractiveObject>> InteractiveObjects;
	UPROPERTY()
	TArray<FInteractiveObjectData> LoadedInteractiveObjects;

	virtual void Load(UTmysSaveGame* SaveGame) override;
	virtual void Save(UTmysSaveGame* SaveGame) override;
};
