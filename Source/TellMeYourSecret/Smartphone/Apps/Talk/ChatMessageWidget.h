#pragma once
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ChatMessageWidget.generated.h"

class UCharacterData;
class UCharacterIconWidget;
class UTextBlock;
class UChatMessage;
UCLASS()
class TELLMEYOURSECRET_API UChatMessageWidget : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

public:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UTextBlock* MessageText;
};
