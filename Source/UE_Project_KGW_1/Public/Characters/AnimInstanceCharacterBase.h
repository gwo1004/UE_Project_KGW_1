// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapons/EWeaponType.h"
#include "AnimInstanceCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_KGW_1_API UAnimInstanceCharacterBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAnimInstanceCharacterBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType WeaponType;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIsCrouch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	bool bCanShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
	bool bIsReload;

};
