// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerableCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class UE_PROJECT_KGW_1_API APlayerableCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerableCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Constructor Settings
	UFUNCTION()
	void SpawnSetUpCamera();

	// EnhancedInput Actions Func
	UFUNCTION()
	void MoveForward(const FInputActionValue& Value);
	UFUNCTION()
	void MoveBack(const FInputActionValue& Value);
	UFUNCTION()
	void MoveRight(const FInputActionValue& Value);
	UFUNCTION()
	void MoveLeft(const FInputActionValue& Value);
	UFUNCTION()
	void LookUp(const FInputActionValue& Value);
	UFUNCTION()
	void ConvertCameraActive(const FInputActionValue& Value);

protected:
	//Camera Comp
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* TPSCameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* FPSCameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera");
	bool bUseFPSCamera;


	
};
