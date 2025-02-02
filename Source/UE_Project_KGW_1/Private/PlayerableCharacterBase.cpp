// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerableCharacterBase.h"
#include <GameFramework\SpringArmComponent.h>
#include <Camera\CameraComponent.h>

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
}

void APlayerableCharacterBase::MoveBack(const FInputActionValue& Value)
{
}

void APlayerableCharacterBase::MoveRight(const FInputActionValue& Value)
{
}

void APlayerableCharacterBase::MoveLeft(const FInputActionValue& Value)
{
}

void APlayerableCharacterBase::LookUp(const FInputActionValue& Value)
{
}

void APlayerableCharacterBase::ConvertCameraActive(const FInputActionValue& Value)
{
}

