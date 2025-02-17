// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainLobbyWidget.generated.h"

/**
 * 
 */

class UButton;

UCLASS()
class UE_PROJECT_KGW_1_API UMainLobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	UUserWidget* OpenUI(const FString& WidgetName);

	UFUNCTION()
	void CloseUI(UUserWidget* Wiget);
public:
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* OptionButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;

protected:
	// TODO : DataAsset/DataTable을 사용한 String 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TMap<FString, TSubclassOf<UUserWidget>> WidgetClass;

private:
	UFUNCTION()
	void OpenInGameLevel();

	UFUNCTION()
	void OpenOptionMenu();
	
};
