// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSSkills/Sova/SovaDrone.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "Components\BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "PlayerGameFramework\PlayableController.h"
#include "DataAssets\DroneInputDataAsset.h"

// Sets default values
ASovaDrone::ASovaDrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetupComponent();

	bUseControllerRotationYaw = true;

	DurationTime = 300.0f;
	MoveSpeed = 10.f;
	Gravity = -50.f;


}

// Called when the game starts or when spawned
void ASovaDrone::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this, &ASovaDrone::DestoryDrone, DurationTime, false);
}

// Called every frame
void ASovaDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASovaDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlayableController* PC = Cast<APlayableController>(GetController()))
		{
			EnhancedInput->BindAction(PC->InputActions->MoveFlight, ETriggerEvent::Triggered, this, &ASovaDrone::MoveFlight);
			EnhancedInput->BindAction(PC->InputActions->MoveForward, ETriggerEvent::Triggered, this, &ASovaDrone::MoveForaward);
			EnhancedInput->BindAction(PC->InputActions->MoveRight, ETriggerEvent::Triggered, this, &ASovaDrone::MoveRight);
			EnhancedInput->BindAction(PC->InputActions->MoveLook, ETriggerEvent::Triggered, this, &ASovaDrone::MoveLook);
			EnhancedInput->BindAction(PC->InputActions->MoveTurn, ETriggerEvent::Triggered, this, &ASovaDrone::MoveTurn);
			EnhancedInput->BindAction(PC->InputActions->DroneAttack, ETriggerEvent::Started, this, &ASovaDrone::DroneAttack);
			EnhancedInput->BindAction(PC->InputActions->DroneExit, ETriggerEvent::Started, this, &ASovaDrone::DroneExit);
		}
	}
}

void ASovaDrone::SetupComponent()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComp;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));

	// TODO : 07번 과제 제출 이후 SpringArm제거 / 1인칭 
	SpringArmComp->SetupAttachment(BoxComp);
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		MeshAsset(TEXT("/Game/Resources/Props/sci_fi_surveillance_drone.sci_fi_surveillance_drone"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	StaticMeshComp->SetupAttachment(BoxComp);
}

void ASovaDrone::DestoryDrone()
{
	if (IsPendingKillPending()) return;

	// Character Posses 로직
	// Controller에서 빙의할 캐릭터 선택하기

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(DestructionTimer);
	}

	if (CameraComp)
	{
		CameraComp->DestroyComponent();
		CameraComp = nullptr;
	}

	if (SpringArmComp)
	{
		SpringArmComp->DestroyComponent();
		SpringArmComp = nullptr;
	}

	if (StaticMeshComp)
	{
		StaticMeshComp->DestroyComponent();
		StaticMeshComp = nullptr;
	}

	if (BoxComp)
	{
		BoxComp->DestroyComponent();
		BoxComp = nullptr;
	}

	Destroy();
}

void ASovaDrone::MoveFlight(const FInputActionValue& Value)
{
	const float MoveInput = Value.Get<float>();
	AddActorLocalOffset(FVector(0.f, 0.f, MoveInput * MoveSpeed));
}

void ASovaDrone::MoveForaward(const FInputActionValue& Value)
{
	const float MoveInput = Value.Get<float>();
	AddActorLocalOffset(FVector(MoveInput * MoveSpeed, 0.f, 0.f));
}

void ASovaDrone::MoveRight(const FInputActionValue& Value)
{
	const float MoveInput = Value.Get<float>();
	AddActorLocalOffset(FVector(0.f, MoveInput * MoveSpeed, 0.f));
}

void ASovaDrone::MoveLook(const FInputActionValue& Value)
{
	const float RotateInput = Value.Get<float>();

	AddControllerPitchInput(RotateInput);
}

void ASovaDrone::MoveTurn(const FInputActionValue& Value)
{
	const float RotateInput = Value.Get<float>();

	AddControllerYawInput(RotateInput);
}

void ASovaDrone::DroneAttack(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("DroneAttack Succeeded"))
}

void ASovaDrone::DroneExit(const FInputActionValue& Value)
{
	DestoryDrone();
}
