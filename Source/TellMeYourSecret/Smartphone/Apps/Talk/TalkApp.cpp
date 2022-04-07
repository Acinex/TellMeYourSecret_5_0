#include "TalkApp.h"

#include "ChatMessage.h"
#include "TellMeYourSecret/Characters/ReputationSystem.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
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

	const UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(this));
	const UReputationSystem* ReputationSystem = GameInstance->GetSubsystem<UReputationSystem>();
	TArray<UChatMessage*> ChatMessages;

	if (!ReputationSystem || !Smartphone)
	{
		return;
	}

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

void UTalkApp::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ContactList->OnItemClicked().AddUObject(this, &UTalkApp::OpenChat);
	SendButton->OnPressed.AddDynamic(this, &UTalkApp::Send);
}

void UTalkApp::SetAvailableMessages(const ECharacterIdentifier Recipient, const TArray<FText> Messages) const
{
	Smartphone->GetPhoneData()->AvailableResponses.Add(Recipient, {Messages});
}

void UTalkApp::OpenChat(const ECharacterIdentifier Identifier)
{
	if (auto [Messages, Character] = Smartphone->GetPhoneData()->GetChat(Identifier); Messages.Num())
	{
		OpenChat(Messages[Messages.Num() - 1]);
	}
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
			FButtonOptions NewOption;
			NewOption.Text = Element;
			ChatComboBox->AddOption(NewOption);
		}
	}

	MessageList->SetListItems(Smartphone->GetPhoneData()->GetChat(Selected->With).Messages);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UTalkApp::Send(UWidgetStudioButtonBase* Button)
{
	FPhoneData* PhoneData = Smartphone->GetPhoneData();

	UChatMessage* ChatMessage = NewObject<UChatMessage>();
	ChatMessage->With = Selected->With;
	ChatMessage->Sender = ECharacterIdentifier::Player;
	ChatMessage->Message = ChatComboBox->GetCurrentOption().Text;

	auto& [Messages, Character] = PhoneData->GetChat(Selected->With);
	Messages.Add(ChatMessage);

	MessageList->SetListItems(Messages);
}

#undef LOCTEXT_NAMESPACE
