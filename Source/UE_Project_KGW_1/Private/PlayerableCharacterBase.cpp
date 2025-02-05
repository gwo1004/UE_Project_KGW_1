// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerableCharacterBase.h"
#include <GameFramework\SpringArmComponent.h>
#include <Camera\CameraComponent.h>
#include <EnhancedInputComponent.h>
#include <InputActionValue.h>
#include "PlayerGameFramework\PlayableController.h"
#include "DataAssets\InputConfigPrimaryDataAsset.h"

APlayerableCharacterBase::APlayerableCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnSetUpCamera();

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
					if (Mapping.InputAction  && Mapping.Trigger != ETriggerEvent::None)
					{
						InputActionMap.Add(Mapping.InputActionEnum, Mapping.InputAction);
						InputTriggers.Add(Mapping.InputActionEnum, Mapping.Trigger);
					}
				}

				for (const auto& Pair : InputActionBindings)
				{
					if (InputActionMap.Contains(Pair.Key))
					{
						UInputAction* IA = InputActionMap[Pair.Key];
						ETriggerEvent Trigger = InputTriggers[Pair.Key];
						if (IA && Trigger != ETriggerEvent::None)
						{
							EnhancedInput->BindAction(IA, Trigger, this, Pair.Value);
						}
					}
				}

				SetupPlayerSkillInputComponent(EnhancedInput);
			}
		}
	}


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

void APlayerableCharacterBase::MoveForward(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("MoveForward Bind Test"));
}

void APlayerableCharacterBase::MoveBack(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("MoveBack Bind Test"));
}

void APlayerableCharacterBase::MoveRight(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("MoveRight Bind Test"));
}

void APlayerableCharacterBase::MoveLeft(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("MoveLeft Bind Test"));
}

void APlayerableCharacterBase::InputJump(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("InputJump Bind Test"));
}

void APlayerableCharacterBase::LookUp(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("LookUp Bind Test"));
}

void APlayerableCharacterBase::InputCrouch(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("InputCrouch Bind Test"));
}

void APlayerableCharacterBase::ConvertCameraActive(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("ConvertCameraActive Bind Test"));
}

void APlayerableCharacterBase::BindMapToDataAsset()
{
	InputActionBindings.Add(EPlayableInputAction::MoveForward,		&APlayerableCharacterBase::MoveForward);
	InputActionBindings.Add(EPlayableInputAction::MoveBack,			&APlayerableCharacterBase::MoveBack);
	InputActionBindings.Add(EPlayableInputAction::MoveRight,		&APlayerableCharacterBase::MoveRight);
	InputActionBindings.Add(EPlayableInputAction::MoveLeft,			&APlayerableCharacterBase::MoveLeft);
	InputActionBindings.Add(EPlayableInputAction::Jump,				&APlayerableCharacterBase::InputJump);
	InputActionBindings.Add(EPlayableInputAction::LookUp,			&APlayerableCharacterBase::LookUp);
	InputActionBindings.Add(EPlayableInputAction::Crouch,			&APlayerableCharacterBase::InputCrouch);
	InputActionBindings.Add(EPlayableInputAction::ConvertCamera,	&APlayerableCharacterBase::ConvertCameraActive);
}

