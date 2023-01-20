#include "UIBase.h"

#include "Widgets/CommonActivatableWidgetContainer.h"

void UUIBase::PushMenu(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	MenuStack->AddWidget(ActivatableWidgetClass);
}

UCommonActivatableWidget* UUIBase::PushPrompt(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	return PromptStack->AddWidget(ActivatableWidgetClass);
}
