// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "DroneInputDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_KGW_1_API UDroneInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveFlight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveTurn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* DroneAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* DroneExit;
};

/*
EnhancedInput의 BindAction시 레퍼런스 경로를 참조하게되면 경로가 변경시에
nullptr이 반환될 수 있습니다.
이러한 경우 유지보수성이 낮다고 볼 수 있어 DataAsset을 통한 Drone 관련 IA들을 DataAsset을 사용하여 관리
또한 간단한 데이터를 관리하기에는 PrimaryDataAsset보다는 DataAsset를 사용한 설계가 효율적이라고 생각하여
UDataAsset 클래스를 사용했습니다.
*/