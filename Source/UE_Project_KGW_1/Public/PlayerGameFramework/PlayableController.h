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

UENUM(BlueprintType)
enum class EControlMode : uint8
{
	TPSCharacter UMETA(DisplayName = "TPSCharacter"),
	FPSCharacter UMETA(DisplayName = "FPSCharacter"),
	DRONE	UMETA(DisplayName = "Drone")
};

UCLASS()
class UE_PROJECT_KGW_1_API APlayableController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlayableController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void SwitchControlMode(EControlMode Mode);

	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TMap<EControlMode, UInputMappingContext*> IMCMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TMap<EControlMode, UDataAsset*> IAMap;
};
