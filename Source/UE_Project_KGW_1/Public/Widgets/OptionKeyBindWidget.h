// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionKeyBindWidget.generated.h"

/**
 * 
 */

class UTextBlock;
class UButton;
class UInputAction;
class UBorder;

USTRUCT(BlueprintType)
struct FKeyBindingData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyBinding")
	FString ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyBinding")
	UInputAction* InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyBinding")
	FKey DefaultKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyBinding")
	FKey CurrentKey;

	FKeyBindingData() {}
	FKeyBindingData(FString ActionName, UInputAction* InputAction, FKey DefaultKey, FKey CurrentKey)
		:ActionName(ActionName), InputAction(InputAction), DefaultKey(DefaultKey), CurrentKey(CurrentKey) {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnKeyBindingUpdated, UOptionKeyBindWidget*, Widget, FKey, NewKey);

UCLASS()
class UE_PROJECT_KGW_1_API UOptionKeyBindWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	void SetKeyBindWidget(const FKeyBindingData& Data);

	UPROPERTY(BlueprintAssignable)
	FOnKeyBindingUpdated OnKeyBindingUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	int32 Index;
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ActionText;
	
	UPROPERTY(meta = (BindWidget))
	UButton* KeyButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KeyText;

	UPROPERTY(meta = (BindWidget))
	UBorder* ActionBorder;


private:
	UFUNCTION()
	void OnKeyButtonClicked();

	FKeyBindingData CurrentData;

};
