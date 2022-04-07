#include "TalkContactWidget.h"

#include "Engine/World.h"

#include "ChatMessage.h"
#include "TellMeYourSecret/Characters/ReputationSystem.h"
#include "Components/TextBlock.h"
#include "TellMeYourSecret/Smartphone/CharacterIconWidget.h"

void UTalkContactWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Super::NativeOnListItemObjectSet(ListItemObject);

	UChatMessage* Message = Cast<UChatMessage>(ListItemObject);

	if (!Message)
	{
		return;
	}

	UGameInstance*     Instance         = Cast<UGameInstance>(GetWorld()->GetGameInstance());
	UReputationSystem* ReputationSystem = Instance->GetSubsystem<UReputationSystem>();

	UCharacterData* CharacterData = ReputationSystem->GetCharacter(Message->Sender);

	CharacterIcon->SetCharacterData(CharacterData);

	Name->SetText(FText::FromString(CharacterData->Name));
}
