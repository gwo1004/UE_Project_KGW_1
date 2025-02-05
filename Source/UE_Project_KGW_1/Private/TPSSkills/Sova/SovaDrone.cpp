// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSSkills/Sova/SovaDrone.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "Components\BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "PlayerGameFramework\PlayableController.h"
#include "DataAssets\DroneInputDataAsset.h"

ASovaDrone::ASovaDrone()
{
	PrimaryActorTick.bCanEverTick = true;
	SetupComponent();

	bUseControllerRotationYaw = true;

	DurationTime = 300.0f;
	MoveSpeed = 20.f;
	Gravity = -5.f;

	CurrentVelocity = FVector::ZeroVector;
	CurrentPitchAngle = 0.f;
	CurrentRollAngle = 0.f;
	TargetPitchAngle = 0.f;
	TargetRollAngle = 0.f;
	MaxOrientation = 20.f;
	InterpSpeed = 1.f;
}

void ASovaDrone::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this, &ASovaDrone::DestoryDrone, DurationTime, false);

	bIsGround = false;
}

void ASovaDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocationAndRotation(DeltaTime);
	CheckGround();
}

void ASovaDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlayableController* PC = Cast<APlayableController>(GetController()))
		{
			EnhancedInput->BindAction(PC->InputActions->MoveFlight, ETriggerEvent::Triggered, this, &ASovaDrone::MoveFlight);
			EnhancedInput->BindAction(PC->InputActions->MoveForward, ETriggerEvent::Triggered, this, &ASovaDrone::MoveForaward);
			EnhancedInput->BindAction(PC->InputActions->MoveForward, ETriggerEvent::Completed, this, &ASovaDrone::StopForaward);
			EnhancedInput->BindAction(PC->InputActions->MoveRight, ETriggerEvent::Triggered, this, &ASovaDrone::MoveRight);
			EnhancedInput->BindAction(PC->InputActions->MoveRight, ETriggerEvent::Completed, this, &ASovaDrone::StopRight);
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
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	BoxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

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


void ASovaDrone::UpdateLocationAndRotation(float DeltaTime)
{
	CurrentRollAngle = FMath::FInterpTo(CurrentRollAngle, TargetRollAngle, DeltaTime, InterpSpeed);
	CurrentPitchAngle = FMath::FInterpTo(CurrentPitchAngle, TargetPitchAngle, DeltaTime, InterpSpeed);

	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Roll = CurrentRollAngle;
	CurrentRotation.Pitch = CurrentPitchAngle;
	SetActorRotation(CurrentRotation);

	CurrentVelocity = FMath::VInterpTo(CurrentVelocity, FVector::ZeroVector, DeltaTime, InterpSpeed);
	
	if (!CurrentVelocity.IsNearlyZero())
	{
		FTransform MoveTransform = GetActorTransform();
		MoveTransform.AddToTranslation(CurrentVelocity * DeltaTime);
		SetActorTransform(MoveTransform);
	}
}

void ASovaDrone::CheckGround()
{
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0.f, 0.f, BoxComp->GetScaledBoxExtent().Z + 10.f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);

	if (bHit)
	{
		bIsGround = true;
		Gravity = 0.f;
		UE_LOG(LogTemp, Log, TEXT("Drone Ground true"));
	}
	else
	{
		bIsGround = false;
		Gravity = -5.f;
		UE_LOG(LogTemp, Log, TEXT("Drone Ground False"));
	}

	if (!bIsGround)
	{
		FVector GravityMovement = FVector(0.f, 0.f, Gravity);
		AddActorWorldOffset(GravityMovement, true);
	}
}

void ASovaDrone::MoveFlight(const FInputActionValue& Value)
{
	const float MoveInput = Value.Get<float>();

	AddActorLocalOffset(FVector(0.f, 0.f, MoveInput * 10.f));
}

void ASovaDrone::MoveForaward(const FInputActionValue& Value)
{
	const float MoveInput = Value.Get<float>();
	TargetPitchAngle = MoveInput * -MaxOrientation;

	FMatrix RotationMatrix = FRotationMatrix(GetActorRotation());
	FVector ForwardDirection = RotationMatrix.GetUnitAxis(EAxis::X);
	ForwardDirection.Z = 0.f;
	
	FVector TranslationOffset = ForwardDirection * MoveInput * MoveSpeed;

	CurrentVelocity.X += TranslationOffset.X;
	CurrentVelocity.Y += TranslationOffset.Y;
}

void ASovaDrone::StopForaward(const FInputActionValue& Value)
{
	TargetPitchAngle = 0.f;
}

void ASovaDrone::MoveRight(const FInputActionValue& Value)
{
	const float MoveInput = Value.Get<float>();
	TargetRollAngle = MoveInput * MaxOrientation;

	FMatrix RotationMatrix = FRotationMatrix(GetActorRotation());
	FVector RightDirection = RotationMatrix.GetUnitAxis(EAxis::Y);
	RightDirection.Z = 0.f;

	FVector TranslationOffset = RightDirection * MoveInput * MoveSpeed;
	CurrentVelocity.X += TranslationOffset.X;
	CurrentVelocity.Y += TranslationOffset.Y;
}

void ASovaDrone::StopRight(const FInputActionValue& Value)
{
	TargetRollAngle = 0.f;
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

/*
TODO:
과제 제출 후 관련 브랜치 작업
자연스러운 비행 / 중력 / 충돌처리
Character <-> Pawn 빙의 
*/