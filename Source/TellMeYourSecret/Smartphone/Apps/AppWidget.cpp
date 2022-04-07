// Fill out your copyright notice in the Description page of Project Settings.

#include "AppWidget.h"
#include "TellMeYourSecret/Smartphone/Smartphone.h"

#include "Kismet/GameplayStatics.h"

bool UAppWidget::Back_Implementation()
{
    return true;
}

void UAppWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    Smartphone = UGameplayStatics::GetGameInstance(this)->GetSubsystem<USmartphone>();
}
