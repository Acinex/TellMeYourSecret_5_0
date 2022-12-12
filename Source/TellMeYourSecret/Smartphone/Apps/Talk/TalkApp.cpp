#include "TalkApp.h"

#include "ChatMessage.h"
#include "TellMeYourSecret/Characters/ReputationSystem.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Log.h"
#include "TellMeYourSecret/Smartphone/Smartphone.h"

#define LOCTEXT_NAMESPACE "TalkApp"

bool UTalkApp::Back_Implementation()
{
	if (MainFrame->ActiveWidgetIndex == 0)
	{
		return true;
	}

	MainFrame->SetActiveWidgetIndex(0);
	return false;
}

void UTalkApp::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateChatList();
}

void UTalkApp::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Smartphone->OnNotification.AddDynamic(this, &UTalkApp::OnNotification);

	ContactList->OnItemClicked().AddUObject(this, &UTalkApp::OpenChat);
	SendButton->OnPressed.AddDynamic(this, &UTalkApp::Send);
}

void UTalkApp::OpenChat(const ECharacterIdentifier Identifier)
{
	if (auto [Messages, Character] = Smartphone->GetPhoneData()->GetChat(Identifier); Messages.Num())
	{
		OpenChat(Messages[Messages.Num() - 1]);
	}
}

UChatMessage* UTalkApp::SendChatMessage(const ECharacterIdentifier Sender, const ECharacterIdentifier Recipient, const FText Message, TArray<FText> Answers)
{
	if (Recipient == ECharacterIdentifier::Player && Sender == ECharacterIdentifier::Player)
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("You can't send a message to yourself"))
		return nullptr;
	}

	if (Recipient != ECharacterIdentifier::Player && Sender != ECharacterIdentifier::Player)
	{
		UE_LOG(LogTellMeYourSecret, Error, TEXT("NPC's don't message each other"))
		return nullptr;
	}

	const ECharacterIdentifier With = Recipient == ECharacterIdentifier::Player ? Sender : Recipient;

	UChatMessage* ChatMessage = NewObject<UChatMessage>(this);
	ChatMessage->Sender = Sender;
	ChatMessage->With = With;
	ChatMessage->Message = Message;

	Smartphone->GetPhoneData()->GetChat(With).Messages.Add(ChatMessage);
	Smartphone->GetPhoneData()->AvailableResponses.Add(Sender, {Answers});
	Smartphone->GetPhoneData()->AvailableResponses.Remove(Recipient);
	UpdateChatList();

	return ChatMessage;
}

void UTalkApp::OpenChat(UObject* SelectedItem)
{
	if (!SelectedItem)
	{
		return;
	}

	Selected = Cast<UChatMessage>(SelectedItem);
	MainFrame->SetActiveWidgetIndex(1);

	ChatComboBox->ClearOptions();

	if (FAvailableMessages* Messages = Smartphone->GetPhoneData()->AvailableResponses.Find(Selected->With))
	{
		for (const FText Element : Messages->Messages)
		{
			ChatComboBox->AddOption(Element.ToString());
		}
	}

	ChatComboBox->SetIsEnabled(ChatComboBox->GetOptionCount() > 0);
	SendButton->SetIsEnabled(ChatComboBox->GetOptionCount() > 0);
	MessageList->SetListItems(Smartphone->GetPhoneData()->GetChat(Selected->With).Messages);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UTalkApp::Send()
{

	if(ChatComboBox->GetSelectedIndex() == -1)
	{
		return;
	}

	if (UChatMessage* ChatMessage = SendChatMessage(ECharacterIdentifier::Player, Selected->With, FText::FromString(ChatComboBox->GetSelectedOption()), {}); Selected && Selected->With == ChatMessage->With)
	{
		MessageList->AddItem(ChatMessage);
	}

	ChatComboBox->ClearOptions();
	ChatComboBox->SetSelectedIndex(-1);
	ChatComboBox->SetIsEnabled(false);
	SendButton->SetIsEnabled(false);
}

void UTalkApp::OnNotification(UAppWidget* App)
{
	if (App != this || !IsVisible())
	{
		return;
	}

	OpenChat(Selected);
	UpdateChatList();
}

void UTalkApp::UpdateChatList()
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this);
	const UReputationSystem* ReputationSystem = GameInstance->GetSubsystem<UReputationSystem>();

	if (!ReputationSystem || !Smartphone)
	{
		return;
	}

	TArray<UChatMessage*> ChatMessages;

	for (const UCharacterData* Element : ReputationSystem->GetKnownCharacters())
	{
		FChat& Chat = Smartphone->GetPhoneData()->GetChat(Element->Identifier);

		UChatMessage* Message = NewObject<UChatMessage>(this);

		if (Chat.Messages.Num())
		{
			Message->Message = Chat.Messages[Chat.Messages.Num() - 1]->Message;
			Message->Sender = Chat.Character;
			Message->With = Chat.Character;
		}
		else
		{
			Message->Message = LOCTEXT("Messages.Empty", "No Messages yet");
			Message->Sender = Chat.Character;
			Message->With = Chat.Character;
		}

		ChatMessages.Add(Message);
	}

	ContactList->SetListItems(ChatMessages);
}

#undef LOCTEXT_NAMESPACE
