// Copyright Acinex Games 2020

#pragma once

#include "CharacterIdentifier.generated.h"

/**
 * Identifies our characters
 */
UENUM(BlueprintType)
enum class ECharacterIdentifier : uint8
{
    ArnoldCobb UMETA(DisplayName="Cobb, Arnold"),
    JulesCobb UMETA(DisplayName="Cobb, Jules"),
    MeganCobb UMETA(DisplayName="Cobb, Megan"),
    VanessaCobb UMETA(DisplayName="Cobb, Vanessa"),

    EstellaStandfield UMETA(DisplayName="Stanfied, EStella"),
    Player UMETA(DisplayName="Player"),
    Father,

    ArtyomSokolov UMETA(DisplayName="Sokolov, Artyom"),
    LarisaSokolov UMETA(DisplayName="Sokolov, Larisa"),
    NatashaSokolov UMETA(DisplayName="Sokolov, Natasha"),

	AineOVeirne UMETA(DisplayName="O'Verine, Aine"),
	SavvieOVeirne UMETA(DisplayName="O'Verine, Savvie")
};
