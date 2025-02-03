// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayableController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UDroneInputDataAsset;

UCLASS()
class UE_PROJECT_KGW_1_API APlayableController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayableController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UDroneInputDataAsset* InputActions;

	//TODO : Character IMC / IA 추가
};
