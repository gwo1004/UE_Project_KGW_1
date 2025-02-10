// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IPlayerSkill.h"
#include "DataAssets\InputConfigPrimaryDataAsset.h"
#include "Weapons\EWeaponType.h"
#include "PlayerableCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UInputAction;
struct FInputActionValue;

UCLASS()
class UE_PROJECT_KGW_1_API APlayerableCharacterBase : public ACharacter, public IIPlayerSkill
{
	GENERATED_BODY()

public:
	APlayerableCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetupPlayerSkillInputComponent(class UEnhancedInputComponent* PlayerInputComponent) {};

	virtual void TPSMainSkill(const FInputActionValue& Value) PURE_VIRTUAL(APlayerableCharacterBase::TPSMainSkill, );
	virtual void TPSFirstSkill(const FInputActionValue& Value) PURE_VIRTUAL(APlayerableCharacterBase::TPSFirstSkill, );
	virtual void TPSSecondSubSkill(const FInputActionValue& Value) PURE_VIRTUAL(APlayerableCharacterBase::TPSSecondSubSkill, );
	virtual void TPSUltSkill(const FInputActionValue& Value) PURE_VIRTUAL(APlayerableCharacterBase::TPSUltSkill, );
	virtual void FPSMainSkill(const FInputActionValue& Value) PURE_VIRTUAL(APlayerableCharacterBase::FPSMainSkill, );
protected:


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
	void InputJump(const FInputActionValue& Value);
	UFUNCTION()
	void LookUp(const FInputActionValue& Value);
	UFUNCTION()
	void InputCrouch(const FInputActionValue& Value);
	UFUNCTION()
	void StopCrouch(const FInputActionValue& Value);
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

	// Convert Camera Mesh Settings
	void VisibilityMesh(const bool isFPSCamera);
private:
	// Constructor Settings
	void SpawnSetUpCamera();
	void SpawnSetUpCharacterComponent();

	// BindActions from DataAssetData;
	TMap<EPlayableInputAction, UInputAction*> InputActionMap;
	TMap<EPlayableInputAction, ETriggerEvent> InputTriggers;
	TMap<EPlayableInputAction, void(APlayerableCharacterBase::*)(const FInputActionValue&)> InputActionBindings;

	void BindMapToDataAsset();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType CurrentWeaponType;

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void SetWeaponType(EWeaponType NewWeaponType);

	EWeaponType GetWeaponType() const { return CurrentWeaponType; }
};
