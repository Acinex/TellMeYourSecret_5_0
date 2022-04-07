#pragma once
#include "GameFramework/Actor.h"
#include "TellMeYourSecret/Characters/CharacterIdentifier.h"
#include "Engine/TriggerBox.h"
#include "TellMeYourSecret/RoomType.h"
#include "RoomManager.generated.h"

USTRUCT(BlueprintType)
struct FRoomBundle
{
    GENERATED_BODY()

    ATriggerBox* GetRoom(ECharacterIdentifier Identifier)
    {
        auto* RoomOfCharacter = PerCharacter.Find(Identifier);

        return RoomOfCharacter ? *RoomOfCharacter : Room;
    }

    UPROPERTY(EditAnywhere)
    TMap<ECharacterIdentifier, ATriggerBox*> PerCharacter;
    UPROPERTY(EditAnywhere)
    ATriggerBox* Room;
};

UCLASS(Blueprintable, BlueprintType)
class ARoomManager : public AActor
{
    GENERATED_BODY()
public:

    ATriggerBox* GetRoom(const ECharacterIdentifier Identifier, ERoomType RoomType)
    {
        FRoomBundle* Found = Rooms.Find(RoomType);

        if (!Found)
        {
            return nullptr;
        }

        return Found->GetRoom(Identifier);
    }

private:
    UPROPERTY(EditAnywhere)
    TMap<ERoomType, FRoomBundle> Rooms;
};
