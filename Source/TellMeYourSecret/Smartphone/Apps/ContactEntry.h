// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ContactEntry.generated.h"

class UImage;
class UTextBlock;
class UCharacterIconWidget;
class UCharacterData;
/**
 * 
 */
UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UContactEntry : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()
public:

    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UCharacterIconWidget* CharacterIcon;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UTextBlock* Name;
};
