// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfigPrimaryDataAsset.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayableInputAction : uint8
{
	MoveForward		UMETA(DisplayName = "Move Forward"),
	MoveBack		UMETA(DisplayName = "Move Back"),
	MoveRight		UMETA(DisplayName = "Move Right"),
	MoveLeft		UMETA(DisplayName = "Move Left"),
	Jump			UMETA(DisplayName = "Jump"),
	LookUp			UMETA(DisplayName = "LookUp"),
	Crouch			UMETA(DisplayName = "Crouch"),
	ConvertCamera	UMETA(DisplayName = "Convert Camera"),
	TPSMainSkill	UMETA(DisplayName = "TPS MainSkill"),
	TPSFirstSkill	UMETA(DisplayName = "TPS FirstSkill"),
	TPSSecondSkill	UMETA(DisplayName = "TPS SecondSkill"),
	TPSUltSkill		UMETA(DisplayName = "TPS UltSkill"),
	FPSMainSkill	UMETA(DisplayName = "FPS MainSkill")

	// TODO : UI관련 조작키 추가
};

USTRUCT(BlueprintType)
struct FPlayerDefaultInputKeyMapping
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPlayableInputAction InputActionEnum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* InputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FKey DefaultKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETriggerEvent Trigger;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly)
	TArray<UInputModifier*> Modifiers;
};

UCLASS(Blueprintable)
class UE_PROJECT_KGW_1_API UInputConfigPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TArray<FPlayerDefaultInputKeyMapping> KeyMappings;
};

/*
UPrimaryDataAsset VS UDataAsset

공통점
UObject 기반으로 동작하여 런타임에서 동적 생성이 가능하다.
IA,UI 설정 값과 같은 게임 데이터를 관리하는 클래스/객체

UDataAsset
- 별도의 검색 기능이 필요하지 않은 경우
- 에디터 레벨에서 데이터를 관리하려는 경우

UPrimaryDataAsset
- AssetManager를 사용하여 런타임 환경에서 특정 데이터 검색 가능
- 멀티플레이에서 모든 클라이언트가 공유해야하는 데이터에 대한 자동관리

UI를 추가한 설계에서 조작키 변경에 대한 기본값 저장 및 런타임 환경에서 검색/수정,
멀티플레이 환경을 고려하여 UPrimaryDataAsset 클래스 기반으로 생성하였습니다.

TODO : 캐릭터 Enhanced Input Branch에서 설계하기
*/