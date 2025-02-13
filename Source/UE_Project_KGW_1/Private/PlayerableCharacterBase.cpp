// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerableCharacterBase.h"
#include <GameFramework\SpringArmComponent.h>
#include <Camera\CameraComponent.h>
#include <EnhancedInputComponent.h>
#include <InputActionValue.h>
#include "PlayerGameFramework\PlayableController.h"
#include "DataAssets\InputConfigPrimaryDataAsset.h"
#include <GameFramework\CharacterMovementComponent.h>
#include "Characters\AnimInstanceCharacterBase.h"

APlayerableCharacterBase::APlayerableCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SpawnSetUpCamera();
	SpawnSetUpCharacterComponent();

	CurrentWeaponType = EWeaponType::Melee;
}

void APlayerableCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerableCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerableCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlayableController* PC = Cast<APlayableController>(GetController()))
		{
			if (UInputConfigPrimaryDataAsset* InputActions = Cast<UInputConfigPrimaryDataAsset>(PC->IAMap[EControlMode::TPSCharacter]))
			{
				BindMapToDataAsset();
				PC->SwitchControlMode(EControlMode::TPSCharacter);

				for (const FPlayerDefaultInputKeyMapping& Mapping : InputActions->KeyMappings)
				{
					if (Mapping.InputAction && Mapping.Trigger != ETriggerEvent::None)
					{
						InputActionMap.Add(Mapping.InputActionEnum, Mapping.InputAction);
					}
				}

				for (const auto& Pair : InputActionBindings)
				{
					if (InputActionMap.Contains(Pair.Key))
					{
						UInputAction* IA = InputActionMap[Pair.Key];
						if (IA)
						{
							for (const FInputBindingInfo& BindingInfo : Pair.Value)
							{
								EnhancedInput->BindAction(IA, BindingInfo.Trigger, this, FName(BindingInfo.FunctionName));
							}
						}
					}
				}

				SetupPlayerSkillInputComponent(EnhancedInput);
			}
		}
	}

}


void APlayerableCharacterBase::MoveForward(const FInputActionValue& Value)
{
	// 애니메이션 블루프린트 및 애니메이션 인스턴스를 통해
	// 캐릭터 클래스 기반의 값에 전달하기위해 AddMovementInput 사용
	// DeltaTime은 CharacterMovementComponent 내부에서 연산되어 프레임에 무관한 일정한 이동속도 유지

	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, Value.Get<float>());

	SetWeaponType(EWeaponType::Rifle);
}

void APlayerableCharacterBase::MoveBack(const FInputActionValue& Value)
{
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, Value.Get<float>());

	SetWeaponType(EWeaponType::Pistol);
}

void APlayerableCharacterBase::MoveRight(const FInputActionValue& Value)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, Value.Get<float>());

	SetWeaponType(EWeaponType::Melee);
}

void APlayerableCharacterBase::MoveLeft(const FInputActionValue& Value)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, Value.Get<float>());
}

void APlayerableCharacterBase::InputJump(const FInputActionValue& Value)
{
	Super::Jump();
}

void APlayerableCharacterBase::LookUp(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void APlayerableCharacterBase::InputCrouch(const FInputActionValue& Value)
{
	if (CanCrouch())
	{
		Super::Crouch();
		UE_LOG(LogTemp, Display, TEXT("InputCrouch Bind Test"));
	}
}

void APlayerableCharacterBase::StopCrouch(const FInputActionValue& Value)
{
	Super::UnCrouch();
	UE_LOG(LogTemp, Display, TEXT("StopCrouch Bind Test"));
}

void APlayerableCharacterBase::ConvertCameraActive(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("ConvertCameraActive Bind Test"));

	bUseFPSCamera = !bUseFPSCamera;
	VisibilityMesh(bUseFPSCamera);
}

void APlayerableCharacterBase::VisibilityMesh(const bool isFPSCamera)
{
	if (GetMesh())
	{
		GetMesh()->SetOwnerNoSee(isFPSCamera);
	}

	TPSCameraComp->SetActive(!isFPSCamera);
	FPSCameraComp->SetActive(isFPSCamera);
}

void APlayerableCharacterBase::SpawnSetUpCamera()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	TPSCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamera"));
	FPSCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));

	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->bUsePawnControlRotation = true;

	TPSCameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	TPSCameraComp->bUsePawnControlRotation = false;

	FPSCameraComp->SetupAttachment(RootComponent);
	FPSCameraComp->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	FPSCameraComp->bUsePawnControlRotation = true;

	bUseFPSCamera = false;

	TPSCameraComp->SetActive(!bUseFPSCamera);
	FPSCameraComp->SetActive(bUseFPSCamera);

	GetMesh()->SetOwnerNoSee(false);
}

void APlayerableCharacterBase::SpawnSetUpCharacterComponent()
{
	//Crouch
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = 60.f;

	// Default = 0.05f;
	GetCharacterMovement()->AirControl = 2.f;
}

void APlayerableCharacterBase::BindMapToDataAsset()
{
	InputActionBindings.Add(EPlayableInputAction::MoveForward, { {ETriggerEvent::Triggered, "MoveForward"} });
	InputActionBindings.Add(EPlayableInputAction::MoveBack, { {ETriggerEvent::Triggered, "MoveBack"} });
	InputActionBindings.Add(EPlayableInputAction::MoveRight, { {ETriggerEvent::Triggered, "MoveRight"} });
	InputActionBindings.Add(EPlayableInputAction::MoveLeft, { {ETriggerEvent::Triggered, "MoveLeft"} });
	InputActionBindings.Add(EPlayableInputAction::Jump, { {ETriggerEvent::Started, "InputJump"} });
	InputActionBindings.Add(EPlayableInputAction::LookUp, { {ETriggerEvent::Triggered, "LookUp"} });
	InputActionBindings.Add(EPlayableInputAction::ConvertCamera, { {ETriggerEvent::Started, "ConvertCameraActive"} });

	InputActionBindings.Add(EPlayableInputAction::Crouch, {
	{ETriggerEvent::Started, "InputCrouch"},
	{ETriggerEvent::Completed, "StopCrouch"}
		});

}

void APlayerableCharacterBase::SetWeaponType(EWeaponType NewWeaponType)
{
	CurrentWeaponType = NewWeaponType;

	UAnimInstanceCharacterBase* AnimInstance = Cast<UAnimInstanceCharacterBase>(GetMesh()->GetAnimInstance());
	if(AnimInstance)
	{
		AnimInstance->WeaponType = NewWeaponType;
	}
}

