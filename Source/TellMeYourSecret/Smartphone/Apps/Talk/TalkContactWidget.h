#pragma once
#include "ChatMessageWidget.h"
#include "Blueprint/UserWidget.h"
#include "TalkContactWidget.generated.h"

class UTextBlock;
UCLASS()
class TELLMEYOURSECRET_API UTalkContactWidget : public UChatMessageWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UTextBlock* Name;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UCharacterIconWidget* CharacterIcon;
};
