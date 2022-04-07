#pragma once
#include "CharacterIdentifier.h"
#include "Engine/DataAsset.h"
#include "CharacterData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TELLMEYOURSECRET_API UCharacterData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterIdentifier Identifier;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;
	UPROPERTY(BlueprintReadOnly, meta=(Deprecated))
	FString OfficialName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString LastName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString PhoneNumber;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture* Image;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FColor SpeakerColor = {255, 255, 255, 255};

	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId(TEXT("Characters"), GetFName()); }

	FString GetFullName() const { return Name + " " + LastName; }
};
