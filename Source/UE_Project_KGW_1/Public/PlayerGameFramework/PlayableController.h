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
class UInputConfigPrimaryDataAsset;

UENUM(BlueprintType)
enum class EControlMode : uint8
{
	NONE			UMETA(DisplayName = "None"),
	TPSCharacter	UMETA(DisplayName = "TPSCharacter"),
	FPSCharacter	UMETA(DisplayName = "FPSCharacter"),
	DRONE			UMETA(DisplayName = "Drone")
};

USTRUCT(BlueprintType)
struct FControlModeMapping
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputConfigPrimaryDataAsset* DataAsset;
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

	UFUNCTION()
	void UpdateCurrentIMC(UInputConfigPrimaryDataAsset* CurrentDataAsset);
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TMap<EControlMode, FControlModeMapping> ControlModeMap;
private:
	EControlMode CurrentMode;
};
