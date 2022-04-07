#include "ChatMessageWidget.h"

#include "ChatMessage.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UChatMessageWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	if (!ListItemObject)
	{
		return;
	}

	UChatMessage* Message = Cast<UChatMessage>(ListItemObject);

	if (!Message)
	{
		return;
	}

	MessageText->SetText(Message->Message);

	if (Message->Sender == ECharacterIdentifier::Player)
	{
		MessageText->SetJustification(ETextJustify::Right);
	}
}

void UChatMessageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MessageText->SetAutoWrapText(true);
}
