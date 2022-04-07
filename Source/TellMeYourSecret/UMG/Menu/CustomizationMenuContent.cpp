// Copyright Acinex Games 2020

#include "CustomizationMenuContent.h"

#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"
#include "TellMeYourSecret/Model/Save/Settings.h"

void UCustomizationMenuContent::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GameInstance = Cast<UTellMeYourSecretGameInstance>(UGameplayStatics::GetGameInstance(this));

	PlayerNameTextBox->OnTextCommitted.AddDynamic(this, &UCustomizationMenuContent::PlayerNameChanged);
}

void UCustomizationMenuContent::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerNameTextBox->SetText(FText::FromString(GameInstance->GetSettings()->PlayerName));
}

void UCustomizationMenuContent::PlayerNameChanged(const FText& PlayerName, ETextCommit::Type CommitMethod)
{
	GameInstance->UpdatePlayerName(PlayerName.ToString());
}
