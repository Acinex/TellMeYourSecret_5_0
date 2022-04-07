#include "MainMenuContainer.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Menu.h"

void UMainMenuContainer::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BackButton->OnClicked.AddDynamic(this, &UMainMenuContainer::Close);
	NameTextBlock->SetText(Name);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UMainMenuContainer::Close()
{
	CloseRequest.Broadcast();
}
