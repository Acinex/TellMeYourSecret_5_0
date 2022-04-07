#pragma once

#include "CoreMinimal.h"
#include "Apps/AppWidget.h"
#include "PhoneData.h"
#include "TellMeYourSecret/UMG/HeadsUpDisplay.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TellMeYourSecret/GameInstances/SaveGameAware.h"

#include "Smartphone.generated.h"

class UTmysSaveGame;
class USaveGame;
class UQuest;
class USmartphoneData;
class UScreenWidget;
class UWidgetComponent;
class UCameraApp;
class UQuestApp;
class UTalkApp;
class UContactApp;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotification, UAppWidget*, App);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenApp, UAppWidget*, App);

UCLASS()
class TELLMEYOURSECRET_API USmartphone : public UGameInstanceSubsystem, public ISaveGameAware
{
	GENERATED_BODY()

public:
	USmartphone();

	UPROPERTY(BlueprintAssignable)
	FOnNotification OnNotification;
	UPROPERTY(BlueprintAssignable)
	FOnOpenApp OnOpenApp;

	UFUNCTION(BlueprintPure)
	FORCEINLINE UContactApp* GetContactApp() const { return ContactApp; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UTalkApp* GetTalkApp() const { return TalkApp; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UQuestApp* GetQuestApp() const { return QuestApp; }

	FORCEINLINE FPhoneData* GetPhoneData() { return &PhoneData; }

	void SetScreen(UScreenWidget* Screen);
	UFUNCTION(BlueprintCallable)
	void SetSmartphoneData(USmartphoneData* InSmartphoneData) { SmartphoneData = InSmartphoneData; }

	UFUNCTION(BlueprintCallable)
	void SetPhoneData(const FPhoneData InPhoneData) { PhoneData = InPhoneData; }

	UFUNCTION(BlueprintCallable)
	void SendChatMessage(const ECharacterIdentifier Sender, const ECharacterIdentifier Recipient, const FText Message, TArray<FText> Messages);

	UFUNCTION(BlueprintCallable)
	void ToggleCamera() const;
	UFUNCTION(BlueprintCallable)
	void DeactivateCamera() const;

	UFUNCTION(BlueprintCallable)
	void OpenApp(UAppWidget* App);
	UFUNCTION(BlueprintCallable)
	void CloseApp(UAppWidget* App);
	UFUNCTION(BlueprintCallable)
	void Back();
	UFUNCTION(BlueprintCallable)
	void Home();
	UFUNCTION(BlueprintCallable)
	void Close() const;
	UFUNCTION(BlueprintCallable)
	void Show();
	UFUNCTION(BlueprintCallable)
	void Hide();

	void SetHUD(UHeadsUpDisplay* HeadsUpDisplay);

	virtual void Save(UTmysSaveGame* SaveGame) override;
	virtual void Load(UTmysSaveGame* SaveGame) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPhoneData PhoneData;
	UPROPERTY()
	TArray<UAppWidget*> OpenApps;
	UPROPERTY()
	TArray<UAppWidget*> Notifications;

private:
	UPROPERTY()
	UContactApp* ContactApp = nullptr;
	UPROPERTY()
	UTalkApp* TalkApp = nullptr;
	UPROPERTY()
	UQuestApp* QuestApp = nullptr;
	UPROPERTY()
	UCameraApp* CameraApp = nullptr;
	UPROPERTY()
	UScreenWidget* ScreenWidget = nullptr;
	UPROPERTY()
	UHeadsUpDisplay* HUD = nullptr;
	UPROPERTY()
	USmartphoneData* SmartphoneData;

	UFUNCTION()
	void Notification(UAppWidget* App);
};
