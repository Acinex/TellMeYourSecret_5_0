#include "PhoneData.h"

FPhoneData::FPhoneData()
{
}

FChat& FPhoneData::GetChat(const ECharacterIdentifier CharacterIdentifier)
{
    for (FChat& Chat : Chats)
    {
        if (Chat.Character == CharacterIdentifier)
        {
            return Chat;
        }
    }

    FChat Chat;
    Chat.Character    = CharacterIdentifier;
    const int32 Index = Chats.Add(Chat);
    return Chats[Index];
}
