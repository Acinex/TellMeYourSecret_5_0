#include "ReputationSystem.h"

#include "NonPlayerCharacter.h"
#include "NonPlayerComponent.h"
#include "Engine/AssetManager.h"
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"
#include "TellMeYourSecret/Model/Save/Settings.h"
#include "TellMeYourSecret/Model/Save/TmysSaveGame.h"

int32 UReputationSystem::GetReputation(const ECharacterIdentifier CharacterIdentifier)
{
	const int* Reputation = Reputations.Find(CharacterIdentifier);
	if (!Reputation)
	{
		return 0;
	}

	return *Reputation;
}

void UReputationSystem::UpdateReputation(const TMap<ECharacterIdentifier, int32> InReputations)
{
	Reputations = InReputations;
}

bool UReputationSystem::Check(const UObject* Object, const ENumericRelation NumericRelation, const int32 Reputation)
{
	if (const ANonPlayerCharacter* Character = Cast<ANonPlayerCharacter>(Object))
	{
		if (const UNonPlayerComponent* NonPlayerComponent = Character->FindComponentByClass<UNonPlayerComponent>())
		{
			return FNumericRelationUtil::Check(NumericRelation, GetReputation(NonPlayerComponent->CharacterData->Identifier), Reputation);
		}
	}

	return false;
}

void UReputationSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> Assets;
	AssetRegistryModule.Get().GetAssetsByClass(FName("CharacterData"), Assets, true);

	for (FAssetData Asset : Assets)
	{
		if (const UCharacterData* Data = Cast<UCharacterData>(Asset.GetAsset()))
		{
			UCharacterData* CharacterData = DuplicateObject(Data, this);
			Characters.Add(Data->Identifier, CharacterData);

			if (Data->Identifier == ECharacterIdentifier::Player)
			{
				const UTellMeYourSecretGameInstance* GameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());
				if (GameInstance && GameInstance->GetSettings())
				{
					CharacterData->Name = GameInstance->GetSettings()->PlayerName;
				}
			}
		}
	}
}

void UReputationSystem::ChangeReputation(const ECharacterIdentifier CharacterIdentifier, const int8 Change)
{
	const int32 Reputation = GetReputation(CharacterIdentifier);

	Reputations.Add(CharacterIdentifier, Reputation + Change);
	if (Change > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Reputation raised by %i to %i"), Change, Reputation + Change));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Reputation lowered by %i to %i"), Change * -1, Reputation + Change));
	}
}

void UReputationSystem::UpdateKnownCharacters(const TSet<ECharacterIdentifier> InKnownCharacters)
{
	KnownCharacters.Empty();

	for (auto CharacterData : GetAllCharacters())
	{
		if (InKnownCharacters.Contains(CharacterData->Identifier))
		{
			KnownCharacters.Add(CharacterData);
		}
	}
}

void UReputationSystem::Load(UTmysSaveGame* SaveGame)
{
	UpdateReputation(SaveGame->GetReputations());
	UpdateKnownCharacters(SaveGame->GetKnownCharacters());
}

void UReputationSystem::Save(UTmysSaveGame* SaveGame)
{
	SaveGame->SetReputations(Reputations);

	TSet<ECharacterIdentifier> Identifiers;
	for (const UCharacterData* CharacterData : KnownCharacters)
	{
		Identifiers.Add(CharacterData->Identifier);
	}

	SaveGame->SetKnownCharacters(Identifiers);
}

TArray<UCharacterData*> UReputationSystem::GetAllCharacters()
{
	TArray<UCharacterData*> AllCharacters;

	GetCharacters().GenerateValueArray(AllCharacters);

	return AllCharacters;
}

TArray<UCharacterData*> UReputationSystem::GetKnownCharacters() const
{
	return KnownCharacters;
}

UCharacterData* UReputationSystem::GetCharacter(const ECharacterIdentifier Identifier)
{
	UCharacterData** CharacterData = Characters.Find(Identifier);
	if (CharacterData)
	{
		return *CharacterData;
	}
	return nullptr;
}

TMap<ECharacterIdentifier, UCharacterData*> UReputationSystem::GetCharacters()
{
	return Characters;
}
