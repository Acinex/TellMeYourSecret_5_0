// Copyright Acinex Games 2020

#include "CameraHud.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "TellMeYourSecret/Smartphone/Smartphone.h"

void UCameraHud::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Smartphone = UGameplayStatics::GetGameInstance(this)->GetSubsystem<USmartphone>();

	SwitchCameraButton->OnClicked.AddDynamic(this, &UCameraHud::SwitchCameraButtonClicked);
	TakePhotoButton->OnClicked.AddDynamic(this, &UCameraHud::TakePhotoButtonClicked);
	BackButton->OnClicked.AddDynamic(this, &UCameraHud::BackButtonClicked);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCameraHud::SwitchCameraButtonClicked()
{
	Smartphone->ToggleCamera();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCameraHud::TakePhotoButtonClicked()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(this, "HighResShot 1");
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UCameraHud::BackButtonClicked()
{
	Smartphone->DeactivateCamera();
	Smartphone->Back();
}
