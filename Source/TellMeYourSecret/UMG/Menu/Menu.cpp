#include "Menu.h"

#include "MainMenuContainer.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/SaveManager.h"
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"
#include "TellMeYourSecret/Model/Save/Settings.h"

void UMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayButton->OnClicked.AddDynamic(this, &UMenu::Play);
	GameButton->OnClicked.AddDynamic(this, &UMenu::ShowGame);
	CustomizationButton->OnClicked.AddDynamic(this, &UMenu::ShowCustomization);
	OptionsButton->OnClicked.AddDynamic(this, &UMenu::ShowOptions);
	AboutButton->OnClicked.AddDynamic(this, &UMenu::ShowAbout);
	QuitButton->OnClicked.AddDynamic(this, &UMenu::Quit);
}

FText UMenu::PlayButtonText() const
{
	UTellMeYourSecretGameInstance* YourSecretGameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());
	if (YourSecretGameInstance->IsPaused())
	{
		return NSLOCTEXT("Menu", "Menu.Continue.Paused", "Continue");
	}

	if (YourSecretGameInstance->GetSettings()->SaveGameInfos.Num() > 0)
	{
		return FText::FormatOrdered(NSLOCTEXT("Menu", "Menu.Continue.Save", "Continue {0}"), FText::FromString(YourSecretGameInstance->GetSettings()->LastSaveSlot.SlotName));
	}

	return NSLOCTEXT("Menu", "Menu.New", "New");
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UMenu::Play()
{
	UTellMeYourSecretGameInstance* YourSecretGameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());

	if (GetWorld()->IsPaused())
	{
		YourSecretGameInstance->UnpauseGame();
	}
	else
	{
		YourSecretGameInstance->GetSubsystem<USaveManager>()->LoadGame(YourSecretGameInstance->GetSettings()->LastSaveSlot.NativeSlotName);
	}
}

void UMenu::ShowGame()
{
	ToggleMenu(GameMenuAnimation);
}

void UMenu::ShowCustomization()
{
	ToggleMenu(CustomizationMenuAnimation);
}

void UMenu::ShowOptions()
{
	ToggleMenu(OptionsMenuAnimation);
}

void UMenu::ShowAbout()
{
	ToggleMenu(AboutMenuAnimation);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UMenu::Quit()
{
	UTellMeYourSecretGameInstance* YourSecretGameInstance = Cast<UTellMeYourSecretGameInstance>(GetGameInstance());

	if (GetWorld()->IsPaused())
	{
		UGameplayStatics::OpenLevel(this, TEXT("MainMenu"));
		YourSecretGameInstance->UnpauseGame();
	}
	else
	{
		UKismetSystemLibrary::QuitGame(this, YourSecretGameInstance->GetPrimaryPlayerController(), EQuitPreference::Quit, false);
	}
}

void UMenu::ToggleMenu(UWidgetAnimation* Animation)
{
	if (CurrentAnimation)
	{
		PlayAnimation(CurrentAnimation, 0, 1, EUMGSequencePlayMode::Reverse);
	}

	if (CurrentAnimation == Animation)
	{
		CurrentAnimation = nullptr;
		return;
	}

	CurrentAnimation = Animation;
	PlayAnimation(CurrentAnimation);
}


void UMenu::CloseActiveMenu()
{
	ToggleMenu(CurrentAnimation);
}
