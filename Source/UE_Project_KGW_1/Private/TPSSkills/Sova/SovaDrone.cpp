// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSSkills/Sova/SovaDrone.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "Components\BoxComponent.h"
#include "EnhancedInputComponent.h"


// Sets default values
ASovaDrone::ASovaDrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetupComponent();

}

// Called when the game starts or when spawned
void ASovaDrone::BeginPlay()
{
	Super::BeginPlay();
	
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

void ASovaDrone::MoveUpDown(const FInputActionValue& Value)
{
}

void ASovaDrone::MoveForawardBack(const FInputActionValue& Value)
{
}

