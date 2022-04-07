#pragma once
#include "RecentCall.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "RecentCallWidget.generated.h"

class UImage;
class UTextBlock;
class UCharacterIconWidget;

UCLASS()
class TELLMEYOURSECRET_API URecentCallWidget : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

public:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCharacterIconWidget* CharacterIcon;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UTextBlock* Name;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UTextBlock* Number;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    URecentCall* RecentCall;
};
