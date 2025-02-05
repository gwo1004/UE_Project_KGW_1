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

	void UpdateLocationAndRotation(float DeltaTime);
	void CheckGround();
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
	void StopForaward(const FInputActionValue& Value);
	UFUNCTION()
	void MoveRight(const FInputActionValue& Value);
	UFUNCTION()
	void StopRight(const FInputActionValue& Value);
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DroneInfo")
	bool bIsGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneInfo")
	float DurationTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DroneInfo")
	FVector CurrentVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DroneInfo")
	float CurrentPitchAngle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DroneInfo")
	float CurrentRollAngle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DroneInfo")
	float TargetPitchAngle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DroneInfo")
	float TargetRollAngle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DroneInfo")
	float MaxOrientation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DroneInfo")
	float InterpSpeed;

protected:
	FTimerHandle DestructionTimer;

};
