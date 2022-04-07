// Copyright Acinex Games 2020

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "TellMeYourSecret/Model/Save/SaveGameInfo.h"
#include "Widgets/WSModernCard.h"

#include "SaveGameWidget.generated.h"

class UWidgetSwitcher;
class USaveManager;
class UBorder;
class UBackgroundBlur;
class UButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClick, FSaveGameInfo, SlotInfo);

/**
 * 
 */
UCLASS()
class TELLMEYOURSECRET_API USaveGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintCallable)
	FOnClick OnLoad;
	UPROPERTY(BlueprintCallable)
	FOnClick OnSave;
	UPROPERTY(BlueprintCallable)
	FOnClick OnDelete;
	UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn))
	FSaveGameInfo SaveGameInfo;

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* LoadButton;
	UPROPERTY(meta=(BindWidget))
	UButton* SaveButton;
	UPROPERTY(meta=(BindWidget))
	UButton* DeleteButton;
	UPROPERTY(meta=(BindWidget))
	UButton* StartGameButton;
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* HoverBox;
	UPROPERTY(meta=(BindWidget))
	UWidgetStudioModernCard* Border;
	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* LayoutSwitcher;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ConfirmDeleteWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ConfirmSaveWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ConfirmCreateWidgetClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ConfirmLoadWidgetClass;

	UFUNCTION(BlueprintPure)
	FText GetSaveDateText() const;

private:
	UPROPERTY()
	USaveManager* SaveManager;

	UFUNCTION()
	void SaveButtonClicked();
	UFUNCTION()
	void DeleteButtonClicked();
	UFUNCTION()
	void LoadButtonClicked();
	UFUNCTION()
	void StartGameButtonClicked();

	UFUNCTION()
	void ConfirmCreate(bool bCreate, FString Name);
	UFUNCTION()
	void ConfirmSave(bool bSave);
	UFUNCTION()
	void ConfirmDelete(bool bDelete);
	UFUNCTION()
	void ConfirmLoad(bool bLoad);
};
