#pragma once

#include "../AppWidget.h"
#include "CoreMinimal.h"
#include "ContactApp.generated.h"

class UCharacterData;
class UCharacterIconWidget;
class UListView;
class UButton;
class UWidgetSwitcher;
UCLASS(BlueprintType)
class TELLMEYOURSECRET_API UContactApp : public UAppWidget
{
    GENERATED_BODY()
public:

    virtual int GetRow() const override { return 2; }
    virtual int GetColumn() const override { return 0; }

    virtual bool Back_Implementation() override;

    virtual void NativeConstruct() override;

    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UWidgetSwitcher* MainSwitcher;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UWidgetSwitcher* Switcher;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* RecentCallsButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* ContactsButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UListView* RecentCallsList;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UListView* ContactsList;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UCharacterIconWidget* CharacterIcon;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* ChatButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(BindWidget))
    UButton* CallButton;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCharacterData* Selected;

private:
    UFUNCTION()
    void ContactChanged(UObject* Item);
    UFUNCTION()
    void OpenChat();
    UFUNCTION()
    void ShowContacts();
    UFUNCTION()
    void ShowCalls();
};
