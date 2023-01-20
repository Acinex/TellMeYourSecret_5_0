// Copyright Acinex Games 2020


#include "MainMenu.h"

#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/SaveManager.h"
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"
#include "TellMeYourSecret/Model/Save/Settings.h"

void UMainMenu::NativeOnActivated()
{
	Super::NativeOnActivated();
	GetDesiredFocusTarget()->SetFocus();
}

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayButton->OnClicked().AddUFunction(this, "Play");
	GameButton->OnClicked().AddUFunction(this, "ShowGame");
	CustomizationButton->OnClicked().AddUFunction(this, "ShowCustomization");
	OptionsButton->OnClicked().AddUFunction(this, "ShowOptions");
	AboutButton->OnClicked().AddUFunction(this, "ShowAbout");
	QuitButton->OnClicked().AddUFunction(this, "Quit");
}

bool UMainMenu::NativeOnHandleBackAction()
{
	Play();
	return true;
}

UWidget* UMainMenu::NativeGetDesiredFocusTarget() const
{
	return PlayButton;
}

void UMainMenu::Play()
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

void UMainMenu::Quit()
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
