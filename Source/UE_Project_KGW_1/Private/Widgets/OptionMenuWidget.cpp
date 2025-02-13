// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/OptionMenuWidget.h"
#include "Components\ScrollBox.h"
#include "Components\Button.h"
#include "Components\TextBlock.h"
#include "Widgets\OptionKeyBindWidget.h"
#include "DataAssets\InputConfigPrimaryDataAsset.h"
#include "PlayerGameFramework\PlayableController.h"

void UOptionMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!CurrentKeyDataAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataAsset is missing"));
		return;
	}

	if (ApplyButton && !ApplyButton->OnClicked.IsBound())
	{
		ApplyButton->OnClicked.AddDynamic(this, &UOptionMenuWidget::OnApplyButtonClicked);
	}
	if (ResetButton && !ResetButton->OnClicked.IsBound())
	{
		ResetButton->OnClicked.AddDynamic(this, &UOptionMenuWidget::OnResetButtonClicked);
	}
}

void UOptionMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();


	PopulateKeyBindings();
}



void UOptionMenuWidget::OnApplyButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Apply Start"));

	for (auto& KeyMapping : CurrentKeyDataAsset->KeyMappings)
	{
		FString ActionName = StaticEnum<EPlayableInputAction>()->GetNameStringByValue(static_cast<int64>(KeyMapping.InputActionEnum));
		if (PendingKeyChanges.Contains(ActionName))
		{
			UE_LOG(LogTemp, Log, TEXT("Apply Change"));
			KeyMapping.CurrentKey = PendingKeyChanges[ActionName];
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Apply End"));

	PendingKeyChanges.Empty();

	if (APlayableController* PC = Cast<APlayableController>(GetOwningPlayer()))
	{
		PC->UpdateCurrentIMC(CurrentKeyDataAsset);
	}
}

void UOptionMenuWidget::OnResetButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Reset Start"));

	for (auto& KeyMapping : CurrentKeyDataAsset->KeyMappings)
	{
		KeyMapping.CurrentKey = KeyMapping.DefaultKey;
	}
	
	if (APlayableController* PC = Cast<APlayableController>(GetOwningPlayer()))
	{
		PC->UpdateCurrentIMC(CurrentKeyDataAsset);
	}

	PendingKeyChanges.Empty();

	PopulateKeyBindings();
	UE_LOG(LogTemp, Log, TEXT("Reset End"));
}

void UOptionMenuWidget::HandleKeyBindingUpdated(UOptionKeyBindWidget* Widget, FKey NewKey)
{
	if (!Widget) return;

	PendingKeyChanges.Add(Widget->CurrentData.ActionName, NewKey);

	UE_LOG(LogTemp, Log, TEXT("Peniding Key : %s -> %s"), *Widget->CurrentData.ActionName, *NewKey.ToString());
}

void UOptionMenuWidget::PopulateKeyBindings()
{
	KeyBindingList->ClearChildren();

	int32 Index = 0;

	//OptionKeyBindWidget ActionName : CurrentKey
	for (const auto& KeyMapping : CurrentKeyDataAsset->KeyMappings)
	{
		UOptionKeyBindWidget* KeyWidget = CreateWidget<UOptionKeyBindWidget>(this, KeyBindWidgetClass);
		if (!KeyWidget) continue;
		if (!KeyMapping.bCanModify) continue;

		FString ActionName = StaticEnum<EPlayableInputAction>()->GetNameStringByValue(static_cast<int64>(KeyMapping.InputActionEnum));
		FKeyBindingData NewData(ActionName, KeyMapping.InputAction, KeyMapping.DefaultKey, KeyMapping.CurrentKey);
		KeyWidget->Index = Index++;
		KeyWidget->SetKeyBindWidget(NewData);

		KeyWidget->OnKeyBindingUpdated.AddDynamic(this, &UOptionMenuWidget::HandleKeyBindingUpdated);
		KeyBindingList->AddChild(KeyWidget);
	}
}
