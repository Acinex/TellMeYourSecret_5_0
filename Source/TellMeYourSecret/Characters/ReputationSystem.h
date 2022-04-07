#pragma once
#include "CharacterData.h"
#include "CharacterIdentifier.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TellMeYourSecret/GameInstances/SaveGameAware.h"
#include "TellMeYourSecret/Utils/NumericRelation.h"

#include "ReputationSystem.generated.h"

class UTmysSaveGame;
UCLASS()
class TELLMEYOURSECRET_API UReputationSystem : public UGameInstanceSubsystem, public ISaveGameAware
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	int32 GetReputation(ECharacterIdentifier CharacterIdentifier);
	void  UpdateReputation(TMap<ECharacterIdentifier, int32> InReputations);
	bool  Check(const UObject* Object, ENumericRelation NumericRelation, const int32 Reputation);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void ChangeReputation(const ECharacterIdentifier CharacterIdentifier, const int8 Change);

	void UpdateKnownCharacters(const TSet<ECharacterIdentifier> InKnownCharacters);

	virtual void Load(UTmysSaveGame* SaveGame) override;
	virtual void Save(UTmysSaveGame* SaveGame) override;

	UFUNCTION(BlueprintPure)
	TArray<UCharacterData*> GetAllCharacters();
	UFUNCTION(BlueprintPure)
	TArray<UCharacterData*> GetKnownCharacters() const;

	UCharacterData* GetCharacter(const ECharacterIdentifier Identifier);

private:
	TMap<ECharacterIdentifier, UCharacterData*> GetCharacters();

	UPROPERTY()
	TMap<ECharacterIdentifier, int32> Reputations;
	UPROPERTY()
	TMap<ECharacterIdentifier, UCharacterData*> Characters;
	UPROPERTY()
	TArray<UCharacterData*> KnownCharacters;
};
