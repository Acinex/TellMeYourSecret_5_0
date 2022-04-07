// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

TSharedRef<SWidget, ESPMode::ThreadSafe> UInteractWidget::RebuildWidget()
{
	if (WidgetTree)
	{
		UHorizontalBox* HBox   = WidgetTree->ConstructWidget<UHorizontalBox>();
		UBorder*        Border = WidgetTree->ConstructWidget<UBorder>();
		TextBlock              = WidgetTree->ConstructWidget<UTextBlock>();

		TextBlock->TextDelegate.BindDynamic(this, &UInteractWidget::GetText);
		WidgetTree->RootWidget = HBox;

		SetAlignmentInViewport(FVector2D(0.5F));

		HBox->AddChild(Border);
		Border->AddChild(TextBlock);

		UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(Border->Slot);

		if (HorizontalBoxSlot)
		{
			HorizontalBoxSlot->VerticalAlignment = VAlign_Bottom;
		}

		Border->SetBrushColor(FLinearColor(0, 0, 0, 0.4F));
	}
	return Super::RebuildWidget();
}

void UInteractWidget::SetText(const FText InText)
{
	Text = InText;
}

void UInteractWidget::NativeTick(const FGeometry& MyGeometry, const float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!Actor)
	{
		return;
	}

	APlayerController* Controller = UGameplayStatics::GetPlayerController(Actor, 0);
	if (!Controller)
	{
		return;
	}

	FVector Origin;
	FVector Extent;
	Actor->GetActorBounds(true, Origin, Extent);

	const FVector Location = Origin + FVector(0.0F, 0.0F, 10.0F);

	FVector2D ScreenLocation;
	Controller->ProjectWorldLocationToScreen(Location, ScreenLocation, false);

	SetPositionInViewport(ScreenLocation, true);
}
