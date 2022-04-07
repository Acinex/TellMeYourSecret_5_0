#include "Smartphone.h"
#include "SmartphoneData.h"
#include "SmartphonePlayer.h"
#include "Apps/QuestApp.h"
#include "Apps/Camera/CameraApp.h"
#include "Apps/Contacts/ContactApp.h"
#include "Apps/Talk/TalkApp.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Screen/ScreenWidget.h"
#include "GameFramework/Character.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/Model/Save/TmysSaveGame.h"

USmartphone::USmartphone()
{
	OnNotification.AddDynamic(this, &USmartphone::Notification);
}

void USmartphone::SetScreen(UScreenWidget* Screen)
{
	if (!Screen)
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("Smartphone-screen can not be null"))
		return;
	}

	ScreenWidget = Screen;
	if (!SmartphoneData)
	{
		return;
	}

	if (SmartphoneData->ContactAppClass)
	{
		ContactApp = CreateWidget<UContactApp>(ScreenWidget, SmartphoneData->ContactAppClass);
		ScreenWidget->AddApp(ContactApp);
	}

	if (SmartphoneData->TalkAppClass)
	{
		TalkApp = CreateWidget<UTalkApp>(ScreenWidget, SmartphoneData->TalkAppClass);
		ScreenWidget->AddApp(TalkApp);
	}

	if (SmartphoneData->QuestAppClass)
	{
		QuestApp = CreateWidget<UQuestApp>(ScreenWidget, SmartphoneData->QuestAppClass);
		ScreenWidget->AddApp(QuestApp);
	}

	if (SmartphoneData->CameraAppClass)
	{
		CameraApp = CreateWidget<UCameraApp>(ScreenWidget, SmartphoneData->CameraAppClass);
		ScreenWidget->AddApp(CameraApp);
	}
}

void USmartphone::SendChatMessage(const ECharacterIdentifier Sender, const ECharacterIdentifier Recipient, const FText Message, TArray<FText> Messages)
{
	if (Recipient == ECharacterIdentifier::Player && Sender == ECharacterIdentifier::Player)
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("You can't send a message to yourself"))
		return;
	}

	if (Recipient != ECharacterIdentifier::Player && Sender != ECharacterIdentifier::Player)
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("NPC's don't message each other"))
		return;
	}

	const ECharacterIdentifier With = Recipient == ECharacterIdentifier::Player ? Sender : Recipient;

	UChatMessage* ChatMessage = NewObject<UChatMessage>(this);
	ChatMessage->Sender = Sender;
	ChatMessage->With = With;
	ChatMessage->Message = Message;

	PhoneData.GetChat(With).Messages.Add(ChatMessage);
}

void USmartphone::ToggleCamera() const
{
	ISmartphonePlayer* PlayerCharacter = Cast<ISmartphonePlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter)
	{
		PlayerCharacter->ToggleSmartphoneCamera();
	}
}

void USmartphone::DeactivateCamera() const
{
	ISmartphonePlayer* PlayerCharacter = Cast<ISmartphonePlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter)
	{
		PlayerCharacter->DeactivateSmartphoneCamera();
	}
}

void USmartphone::OpenApp(UAppWidget* App)
{
	if (ScreenWidget)
	{
		ScreenWidget->ShowApp(App);
	}

	OpenApps.AddUnique(App);
	OnOpenApp.Broadcast(App);

	if (HUD && Notifications.Contains(App))
	{
		HUD->HideNotification();
		Notifications.Remove(App);
	}
}

void USmartphone::CloseApp(UAppWidget* App)
{
	App->Close();
	ScreenWidget->HideApp(App);
	OpenApps.Remove(App);

	if (OpenApps.Num() != 0)
	{
		ScreenWidget->ShowApp(OpenApps[0]);
	}
}

void USmartphone::Back()
{
	if (OpenApps.Num() == 0)
	{
		Close();
		return;
	}

	if (OpenApps[0]->Back())
	{
		CloseApp(OpenApps[0]);
	}
}

void USmartphone::Home()
{
	for (UAppWidget* App : OpenApps)
	{
		ScreenWidget->HideApp(App);
	}

	OpenApps.Empty();
}

void USmartphone::Close() const
{
	ISmartphonePlayer* PlayerCharacter = Cast<ISmartphonePlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (PlayerCharacter)
	{
		PlayerCharacter->ToggleSmartphone();
	}
}

void USmartphone::Show()
{
	ISmartphonePlayer* PlayerCharacter = Cast<ISmartphonePlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!PlayerCharacter)
	{
		return;
	}

	Notifications.Empty();

	if (HUD)
	{
		HUD->HideNotification();
	}
}

void USmartphone::Hide()
{
}

void USmartphone::SetHUD(UHeadsUpDisplay* HeadsUpDisplay)
{
	HUD = HeadsUpDisplay;
}

void USmartphone::Notification(UAppWidget* App)
{
	if (OpenApps.Contains(App))
	{
		return;
	}

	Notifications.AddUnique(App);

	if (SmartphoneData && SmartphoneData->NotificationSound)
	{
		UGameplayStatics::PlaySound2D(this, SmartphoneData->NotificationSound);
	}

	if (SmartphoneData && HUD)
	{
		HUD->ShowNotification(SmartphoneData->NotificationImage);
	}
}

void USmartphone::Save(UTmysSaveGame* SaveGame)
{
	SaveGame->SetPhoneData(PhoneData);
}

void USmartphone::Load(UTmysSaveGame* SaveGame)
{
	PhoneData = SaveGame->GetPhoneData();
}
