#pragma once

#include "CoreMinimal.h"

#include "Apps/Talk/ChatMessage.h"
#include "TellMeYourSecret/Characters/CharacterIdentifier.h"

#include "PhoneData.generated.h"

USTRUCT(BlueprintType)
struct TELLMEYOURSECRET_API FChat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UChatMessage*> Messages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterIdentifier Character;
};

UENUM(BlueprintType)
enum class ECallType : uint8
{
	Answered,
	Missed,
	Outgoing
};

USTRUCT(BlueprintType)
struct TELLMEYOURSECRET_API FCall
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ECharacterIdentifier Character;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Amount = 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ECallType CallType;
};

USTRUCT(BlueprintType)
struct TELLMEYOURSECRET_API FAvailableMessages
{
	GENERATED_BODY()

	TArray<FText> Messages;
};

USTRUCT(BlueprintType)
struct TELLMEYOURSECRET_API FPhoneData
{
	GENERATED_BODY()

	FPhoneData();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FCall> Calls;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FChat> Chats;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<ECharacterIdentifier, FAvailableMessages> AvailableResponses;

	FChat& GetChat(ECharacterIdentifier CharacterIdentifier);

	
	friend FArchive& operator<<(FArchive& Ar, FPhoneData& Data)
	{
		return Ar;
	}
};
