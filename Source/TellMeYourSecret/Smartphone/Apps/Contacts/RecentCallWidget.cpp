#include "RecentCallWidget.h"


#include "TellMeYourSecret/Characters/CharacterData.h"
#include "Components/TextBlock.h"
#include "TellMeYourSecret/Smartphone/CharacterIconWidget.h"

void URecentCallWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    RecentCall = Cast<URecentCall>(ListItemObject);

    if (!RecentCall)
    {
        return;
    }

    CharacterIcon->SetCharacterData(RecentCall->CharacterData);

    FString Append;
    if (RecentCall->Call.Amount > 1)
    {
        Append = FString::Printf(TEXT(" (%d)"), RecentCall->Call.Amount);
    }

    Name->SetText(FText::FromString(RecentCall->CharacterData->GetFullName().Append(Append)));
    Number->SetText(FText::FromString(RecentCall->CharacterData->PhoneNumber));
}
