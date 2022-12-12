// Copyright Acinex Games 2020


#include "KeypadWidget.h"

#include "TellMeYourSecret/GameInstances/TellMeYourSecretGameInstance.h"
#include "TellMeYourSecret/Model/Save/TmysSaveGame.h"

void UKeypadWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UKeypadWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Key0->OnReleased.AddDynamic(this, &UKeypadWidget::KeyPressed);
	// Key1->OnReleased.AddDynamic(this, &UKeypadWidget::KeyPressed);
	// Key2->OnReleased.AddDynamic(this, &UKeypadWidget::KeyPressed);
	// Key3->OnReleased.AddDynamic(this, &UKeypadWidget::KeyPressed);
	// Key4->OnReleased.AddDynamic(this, &UKeypadWidget::KeyPressed);
	// Key5->OnReleased.AddDynamic(this, &UKeypadWidget::KeyPressed);
	// Key6->OnReleased.AddDynamic(this, &UKeypadWidget::KeyPressed);
	// Key7->OnReleased.AddDynamic(this, &UKeypadWidget::KeyPressed);
	// Key8->OnReleased.AddDynamic(this, &UKeypadWidget::KeyPressed);
	// Key9->OnReleased.AddDynamic(this, &UKeypadWidget::KeyPressed);
	//
	// BackKey->OnReleased.AddDynamic(this, &UKeypadWidget::Back);
	// ConfirmKey->OnReleased.AddDynamic(this, &UKeypadWidget::Confirm);
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
// void UKeypadWidget::KeyPressed(UWidgetStudioButtonBase* CallingButton)
// {
// 	if (Code.Len() == 4)
// 	{
// 		return;
// 	}
//
// 	if (CallingButton == Key0)
// 	{
// 		Code.Append("0");
// 	}
// 	else if (CallingButton == Key1)
// 	{
// 		Code.Append("1");
// 	}
// 	else if (CallingButton == Key2)
// 	{
// 		Code.Append("2");
// 	}
// 	else if (CallingButton == Key3)
// 	{
// 		Code.Append("3");
// 	}
// 	else if (CallingButton == Key4)
// 	{
// 		Code.Append("4");
// 	}
// 	else if (CallingButton == Key5)
// 	{
// 		Code.Append("5");
// 	}
// 	else if (CallingButton == Key6)
// 	{
// 		Code.Append("6");
// 	}
// 	else if (CallingButton == Key7)
// 	{
// 		Code.Append("7");
// 	}
// 	else if (CallingButton == Key8)
// 	{
// 		Code.Append("8");
// 	}
// 	else if (CallingButton == Key9)
// 	{
// 		Code.Append("9");
// 	}
//
// 	Display->SetText(FText::FromString(Code));
// }
//
// void UKeypadWidget::Back(UWidgetStudioButtonBase* CallingButton)
// {
// 	if (Code.Len())
// 	{
// 		Code = Code.Left(Code.Len() - 1);
// 	}
// 	else
// 	{
// 		RemoveFromParent();
// 		GetOwningPlayer()->bShowMouseCursor = false;
// 		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
// 	}
//
// 	Display->SetText(FText::FromString(Code));
// }
//
// // ReSharper disable once CppMemberFunctionMayBeConst
// void UKeypadWidget::Confirm(UWidgetStudioButtonBase* CallingButton)
// {
// 	const FString GateCode = Cast<UTellMeYourSecretGameInstance>(GetGameInstance())->GetGameValues()->GateCode;
//
// 	if (Code == GateCode)
// 	{
// 		OnSucceed.Broadcast();
// 		RemoveFromParent();
// 		GetOwningPlayer()->bShowMouseCursor = false;
// 		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
// 	}
// }
