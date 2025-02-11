// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/OptionMenuWidget.h"
#include "Components\ScrollBox.h"
#include "Components\Button.h"
#include "Widgets\OptionKeyBindWidget.h"
#include "DataAssets\InputConfigPrimaryDataAsset.h"

void UOptionMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!DefaultKeyDataAsset || !CurrentKeyDataAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataAsset is missing"));
		return;
	}

	KeyBindingList->ClearChildren();

	if (ResetButton)
	{
		ResetButton->OnClicked.AddDynamic(this, &UOptionMenuWidget::OnResetButtonClicked);
	}

	int32 Index = 0;

	for (const auto& KeyMapping : CurrentKeyDataAsset->KeyMappings)
	{
		UOptionKeyBindWidget* KeyWidget = CreateWidget<UOptionKeyBindWidget>(this, KeyBindWidgetClass);
		if (!KeyWidget) continue;
		
		FString ActionName = StaticEnum<EPlayableInputAction>()->GetNameStringByValue(static_cast<int64>(KeyMapping.InputActionEnum));
		FKeyBindingData NewData(ActionName, KeyMapping.InputAction, KeyMapping.DefaultKey, KeyMapping.DefaultKey);
		KeyWidget->Index = Index++;
		KeyWidget->SetKeyBindWidget(NewData);
		
		KeyBindingList->AddChild(KeyWidget);
	}
}

void UOptionMenuWidget::OnResetButtonClicked()
{

}

void UOptionMenuWidget::HandleKeyBindingUpdated(UOptionKeyBindWidget* Widget, FKey NewKey)
{
}

void UOptionMenuWidget::PopulateKeyBindings()
{

}
