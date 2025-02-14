// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionMenuWidget.generated.h"

/**
 * 
 */

class UScrollBox;
class UButton;
class UOptionKeyBindWidget;
class UInputConfigPrimaryDataAsset;

UCLASS()
class UE_PROJECT_KGW_1_API UOptionMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* KeyBindingList;

	UPROPERTY(meta = (BindWidget))
	UButton* ApplyButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetButton;

	UPROPERTY(EditAnywhere, Category = "KeyBindings")
	UInputConfigPrimaryDataAsset* CurrentKeyDataAsset;

	UPROPERTY(EditAnywhere, Category = "KeyBindings")
	TSubclassOf<UOptionKeyBindWidget> KeyBindWidgetClass;

private:
	TMap<FString, FKey> PendingKeyChanges;

	UFUNCTION()
	void OnApplyButtonClicked();

	UFUNCTION()
	void OnResetButtonClicked();

	UFUNCTION()
	void HandleKeyBindingUpdated(UOptionKeyBindWidget* Widget, FKey NewKey);

	void PopulateKeyBindings();
};
