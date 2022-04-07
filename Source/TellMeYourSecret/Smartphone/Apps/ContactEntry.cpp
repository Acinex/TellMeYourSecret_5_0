// Copyright Acinex Games 2020

#include "ContactEntry.h"


#include "TellMeYourSecret/Characters/CharacterData.h"
#include "Components/TextBlock.h"
#include "TellMeYourSecret/Smartphone/CharacterIconWidget.h"

void UContactEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    UCharacterData* Contact = Cast<UCharacterData>(ListItemObject);
    CharacterIcon->SetCharacterData(Contact);
    Name->SetText(FText::FromString(Contact->GetFullName()));
}
