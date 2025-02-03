// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSSkills/Sova/SovaDrone.h"

// Sets default values
ASovaDrone::ASovaDrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

