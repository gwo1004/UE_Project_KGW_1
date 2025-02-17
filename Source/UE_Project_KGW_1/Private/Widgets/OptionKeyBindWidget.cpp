// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/OptionKeyBindWidget.h"
#include "Components\Button.h"
#include "Components\TextBlock.h"
#include "Components\Border.h"

void UOptionKeyBindWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	bIsFocusable = true;

	if (KeyButton)
	{
		KeyButton->OnClicked.AddDynamic(this, &UOptionKeyBindWidget::OnKeyButtonClicked);
	}
}

void UOptionKeyBindWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

FReply UOptionKeyBindWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (bIsClickedButton)
	{
		FKey NewKey = InKeyEvent.GetKey();
		OnKeyBindingUpdated.Broadcast(this, NewKey);

		if (KeyText)
		{
			KeyText->SetText(NewKey.GetDisplayName());
		}

		bIsClickedButton = false;

		
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UOptionKeyBindWidget::SetKeyBindWidget(const FKeyBindingData& Data)
{
	CurrentData = Data;

	if (ActionText)
	{
		ActionText->SetText(FText::FromString(Data.ActionName));
	}

	if (KeyText)
	{
		KeyText->SetText(FText::FromString(Data.CurrentKey.ToString()));
	}

	if (ActionBorder && KeyButton)
	{
		if (Index % 2 == 1)
		{
			ActionBorder->SetBrushColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.3f));
			KeyButton->BackgroundColor = (FLinearColor(1.0f, 1.0f, 1.0f, 0.3f));
		}
		else
		{
			ActionBorder->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.3f));
			KeyButton->BackgroundColor = (FLinearColor(0.f, 0.f, 0.f, 0.3f));
		}
	}
}

void UOptionKeyBindWidget::OnKeyButtonClicked()
{
	bIsClickedButton = true;

	if (KeyText)
	{
		KeyText->SetText(FText::FromString(TEXT("-")));
	}
}
