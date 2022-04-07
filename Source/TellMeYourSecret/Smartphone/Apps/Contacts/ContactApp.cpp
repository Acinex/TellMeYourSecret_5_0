#include "ContactApp.h"


#include "RecentCall.h"
#include "TellMeYourSecret/Characters/ReputationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "TellMeYourSecret/Smartphone/CharacterIconWidget.h"
#include "TellMeYourSecret/Smartphone/Smartphone.h"
#include "TellMeYourSecret/Smartphone/Apps/Talk/TalkApp.h"

bool UContactApp::Back_Implementation()
{
	if (MainSwitcher->GetActiveWidgetIndex() == 0)
	{
		return true;
	}

	MainSwitcher->SetActiveWidgetIndex(0);
	return false;
}

void UContactApp::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(this));

	UReputationSystem* ReputationSystem = GameInstance->GetSubsystem<UReputationSystem>();

	const TArray<UCharacterData*> KnownCharacters = ReputationSystem->GetKnownCharacters();

	ContactsList->SetListItems(KnownCharacters);
	RecentCallsList->ClearListItems();

	for (FCall Call : Smartphone->GetPhoneData()->Calls)
	{
		URecentCall* RecentCall   = NewObject<URecentCall>(this);
		RecentCall->Call          = Call;
		RecentCall->CharacterData = ReputationSystem->GetCharacter(Call.Character);
		RecentCallsList->AddItem(RecentCall);
	}
}

void UContactApp::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ContactsList->OnItemSelectionChanged().AddUObject(this, &UContactApp::ContactChanged);
	ChatButton->OnClicked.AddDynamic(this, &UContactApp::OpenChat);

	ContactsButton->OnClicked.AddDynamic(this, &UContactApp::ShowContacts);
	RecentCallsButton->OnClicked.AddDynamic(this, &UContactApp::ShowCalls);
}

void UContactApp::ContactChanged(UObject* Item)
{
	Selected = Cast<UCharacterData>(Item);

	CharacterIcon->SetCharacterData(Selected);
	MainSwitcher->SetActiveWidgetIndex(1);
}

void UContactApp::OpenChat()
{
	UTalkApp* TalkApp = Smartphone->GetTalkApp();
	Smartphone->OpenApp(TalkApp);
	TalkApp->OpenChat(Selected->Identifier);
}

void UContactApp::ShowContacts()
{
	Switcher->SetActiveWidgetIndex(1);
}

void UContactApp::ShowCalls()
{
	Switcher->SetActiveWidgetIndex(0);
}
