#pragma once
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "CharacterIconWidget.generated.h"

class UImage;
class UCharacterData;

UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UCharacterIconWidget : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void SetCharacterData(UCharacterData* InCharacterData);
    UFUNCTION(BlueprintPure)
    UCharacterData* GetCharacterData() const { return CharacterData; }

    void SetSelected(const bool bSelected);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UImage* BrushImage;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UImage* ContactImage;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FLinearColor Color;

    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
    virtual void NativeConstruct() override;

private:
    UPROPERTY()
    UCharacterData* CharacterData;

    UFUNCTION(BlueprintPure)
    FSlateBrush GetBrush();

    UFUNCTION(BlueprintPure)
    FSlateBrush GetImage();
};
