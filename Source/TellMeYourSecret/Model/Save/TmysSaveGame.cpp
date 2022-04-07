// Fill out your copyright notice in the Description page of Project Settings.

#include "TmysSaveGame.h"

UTmysSaveGame::UTmysSaveGame()
{
	bNew            = true;
	Map             = TEXT("Whitebay");
	KnownCharacters = {ECharacterIdentifier::EstellaStandfield};

	CurrentTime = FDateTime::Now();
	CurrentTime = {CurrentTime.GetYear(), CurrentTime.GetMonth(), CurrentTime.GetDay(), 8};
}

FPhoneData UTmysSaveGame::GetPhoneData()
{
	return PhoneData;
}

void UTmysSaveGame::SetPhoneData(FPhoneData& Value)
{
	PhoneData = Value;
}

TSet<ECharacterIdentifier> UTmysSaveGame::GetKnownCharacters()
{
	return KnownCharacters;
}

void UTmysSaveGame::SetKnownCharacters(const TSet<ECharacterIdentifier> Value)
{
	KnownCharacters = Value;
}

TMap<ECharacterIdentifier, int32> UTmysSaveGame::GetReputations()
{
	return Reputations;
}

void UTmysSaveGame::SetReputations(const TMap<ECharacterIdentifier, int32> Value)
{
	Reputations = Value;
}
