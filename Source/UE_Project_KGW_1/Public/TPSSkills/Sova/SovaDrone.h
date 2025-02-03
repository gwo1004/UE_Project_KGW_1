// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SovaDrone.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;

struct FInputActionValue;

UCLASS()
class UE_PROJECT_KGW_1_API ASovaDrone : public APawn
{
	GENERATED_BODY()

public:
	ASovaDrone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetupComponent();

	void DestoryDrone();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DroneInfo")
	float MoveSpeed;

protected:
	UFUNCTION()
	void MoveFlight(const FInputActionValue& Value);
	UFUNCTION()
	void MoveForaward(const FInputActionValue& Value);
	UFUNCTION()
	void MoveRight(const FInputActionValue& Value);
	UFUNCTION()
	void MoveLook(const FInputActionValue& Value);
	UFUNCTION()
	void MoveTurn(const FInputActionValue& Value);
	UFUNCTION()
	void DroneAttack(const FInputActionValue& Value);
	UFUNCTION()
	void DroneExit(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneInfo")
	float Gravity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneInfo")
	float DurationTime;

protected:
	FTimerHandle DestructionTimer;

};
